# Source: KACTL
# Added custom escaping function,
# changed include parsing, error handling and overall structure

from dataclasses import dataclass
import re

@dataclass
class File:
  headers: dict[str, str]
  includes: list[str]
  source: str
  warnings: str

class FileException(Exception):
  pass

COMMENT_TYPES = [
  ('/**', '*/'),
  ("'''", "'''"),
  ('"""', '"""'),
]

def find_start_comment(source, start=None):
  first = (-1, -1, None)
  for s, e in COMMENT_TYPES:
    i = source.find(s, start)
    if i != -1 and (i < first[0] or first[0] == -1):
      first = (i, i + len(s), e)

  return first

KNOWN_COMMANDS = ['Opis', 'Czas']
REQUIRED_COMMANDS = []

def process_with_comments(instream):
  includelist = []
  # Read lines from source file
  try:
    lines = instream.readlines()
  except:
    raise FileException('Could not read source')
  nlines = list()
  for line in lines:
    if 'exclude-line' in line:
      continue
    if 'include-line' in line:
      line = line.replace('// ', '', 1)
    had_comment = "///" in line
    keep_include = 'keep-include' in line
    # Remove /// comments
    line = line.split("///")[0].rstrip()
    # Remove '#pragma once' lines
    if line == "#pragma once":
      continue
    if had_comment and not line:
      continue
    # Check includes
    include = parse_include(line)
    if include is not None and not keep_include:
      includelist.append(include)
      continue
    nlines.append(line)
  # Remove and process multiline comments
  source = '\n'.join(nlines)
  nsource = ''
  start, start2, end_str = find_start_comment(source)
  end = 0
  commands = {}
  while start >= 0:
    nsource = nsource.rstrip() + source[end:start]
    end = source.find(end_str, start2)
    if end<start:
      raise FileException("Invalid %s %s comments." % (source[start:start2], end_str))
    comment = source[start2:end].strip()
    end += len(end_str)
    start, start2, end_str = find_start_comment(source, end)

    commentlines = comment.split('\n')
    command = None
    value = ""
    for cline in commentlines:
      allow_command = False
      cline = cline.strip()
      if cline.startswith('*'):
        cline = cline[1:].strip()
        allow_command = True
      ind = cline.find(':')
      if allow_command and ind != -1 and ' ' not in cline[:ind] and cline[0].isalpha() and cline[0].isupper():
        if command:
          if command not in KNOWN_COMMANDS:
            raise FileException(f'Unknown command: {command}')
          commands[command] = value.lstrip()
        command = cline[:ind]
        value = cline[ind+1:].strip()
      else:
        value = value + '\n' + cline
    if command:
      if command not in KNOWN_COMMANDS:
        raise FileException(f'Unknown command: {command}')
      commands[command] = value.lstrip()

  for rcommand in sorted(set(REQUIRED_COMMANDS) - set(commands)):
    raise FileException(f'Missing command: {rcommand}')
  if end>=0:
    nsource = nsource.rstrip() + source[end:]
  nsource = nsource.strip()
  return verify(commands, includelist, nsource)

def process_raw(instream):
  try:
    source = instream.read().strip()
    return verify({}, [], source)
  except:
    raise FileError('Could not read source')

def parse_include(line):
  line = line.strip()
  if line.startswith("#include"):
    s = line[8:].strip()
    return s if not s.startswith('<') else None
  return None

def escape(s):
  # Escape `...` => \src{...}
  s = re.sub(r'`([^`]*)`', r'\\src{\1}', s)
  # Escape O(...) => \bigo{...}
  t = ''
  st = []
  i = 0
  cnt = 0
  while i < len(s):
    if i < len(s) - 1 and s[i:i+2] == 'O(':
      cnt += 1
      st.append(True)
      t += r'\bigo{'
      i += 2
      continue
    if cnt > 0 and s[i] == ')':
      if len(st) == 0:
        raise FileException('Invalid bracket sequence in O()')
      b = st.pop()
      t += '}' if b else ')'
      cnt -= 1 if b else 0
      i += 1
      continue
    t += s[i]
    if cnt > 0 and s[i] == '(':
      st.append(False)
    i += 1
  if len(st) != 0:
    raise FileException('Invalid bracket sequence in O()')
  return t

COLUMN_LIMIT = 63

def verify(headers, includes, source):
  for key, val in headers.items():
    headers[key] = escape(val)
  warn = ''    
  if len(max(source.split('\n'), key=len)) > COLUMN_LIMIT:
    warn = 'Line length exceeds column limit'
  return File(headers, includes, source, warn)
  
