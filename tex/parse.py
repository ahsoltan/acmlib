# Source: KACTL
import argparse
import re
import os

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
      assert(len(st) > 0)
      b = st.pop()
      t += '}' if b else ')'
      cnt -= 1 if b else 0
      i += 1
      continue
    t += s[i]
    if cnt > 0 and s[i] == '(':
      st.append(False)
    i += 1
  assert(len(st) == 0)
  return t

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

def processwithcomments(caption, head, instream, outstream, listingslang):
  knowncommands = ['Opis', 'Stosowanie', 'Czas']
  requiredcommands = []
  includelist = []
  error = ""
  warning = ""
  # Read lines from source file
  try:
    lines = instream.readlines()
  except:
    error = "Could not read source."
    lines = []
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
  while start >= 0 and not error:
    nsource = nsource.rstrip() + source[end:start]
    end = source.find(end_str, start2)
    if end<start:
      error = "Invalid %s %s comments." % (source[start:start2], end_str)
      break
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
          if command not in knowncommands:
            error = error + "Unknown command: " + command + ". "
          commands[command] = value.lstrip()
        command = cline[:ind]
        value = cline[ind+1:].strip()
      else:
        value = value + '\n' + cline
    if command:
      if command not in knowncommands:
        error = error + "Unknown command: " + command + ". "
      commands[command] = value.lstrip()
  for rcommand in sorted(set(requiredcommands) - set(commands)):
    error = error + "Missing command: " + rcommand + ". "
  if end>=0:
    nsource = nsource.rstrip() + source[end:]
  nsource = nsource.strip()

  # Produce output
  out = []
  if warning:
    out.append(r"\acmwarning{%s: %s}" % (caption, warning))
  if error:
    out.append(r"\acmerror{%s: %s}" % (caption, error))
  else:
    generate(caption, head, commands, includelist, nsource, listingslang, out)

  for line in out:
    print(line, file=outstream)

def processraw(caption, head, instream, outstream, listingslang = 'raw'):
  try:
    source = instream.read().strip()
    out = []
    generate(caption, head, {}, [], source, listingslang, out)
    for line in out:
      print(line, file=outstream)
  except:
    print(r"\acmerror{Could not read source.}", file=outstream)

def parse_include(line):
  line = line.strip()
  if line.startswith("#include"):
    s = line[8:].strip()
    return s if not s.startswith('<') else None
  return None

def generate(caption, head, headers, includes, src, lang, out):
  out.append(r'\ctitle{%s}' % caption)
  for key, val in headers.items():
    out.append(r'\cheader{%s}{%s}' % (key, escape(val)))
  # TODO: handle includes
  # TODO: verify column limit (63)
  out.append(r'\smallskip')
  out.append(r'\hrule')
  out.append(r'\marks\hdrmark{%s}' % head)
  out.append(r'\begin{lstlisting}[language=%s]' % lang)
  out.append(src)
  out.append(r'\end{lstlisting}')

def parse(args):
  caption = os.path.basename(args.input.name)
  head = os.path.splitext(caption)[0]
  args.head.write(f'{head}\n')
  args.head.close()
  if args.lang == 'C++' or args.lang == 'Python':
    processwithcomments(caption, head, args.input, args.output, args.lang)
  else: 
    processraw(caption, head, args.input, args.output, args.lang)
  args.output.close()

def pop(args):
  seg = args.data.split(';')
  if not seg[0]:
    return
  lines = [x.strip() for x in args.head.readlines()]
  first = lines.index(seg[0])
  last = lines.index(seg[1])
  sub = lines[first:last + 1]
  length = len(''.join(sub))
  font_size = 10 if length <= 150 else 8
  f = args.output
  f.write(r'\fontsize{%s}{%s}\textbf{%s}' % (font_size, font_size, r'\enspace{}'.join(sub)))
  f.close()

def main():
  parser = argparse.ArgumentParser()
  subparsers = parser.add_subparsers(required=True)

  pparse = subparsers.add_parser('parse')
  pparse.add_argument('input', type=argparse.FileType('r'))
  pparse.add_argument('lang', choices=['C++', 'Python', 'bash', 'make', 'raw'])
  pparse.add_argument('output', type=argparse.FileType('w'))
  pparse.add_argument('head', type=argparse.FileType('a'))
  pparse.set_defaults(func=parse)

  ppop = subparsers.add_parser('pop')
  ppop.add_argument('data', type=str)
  ppop.add_argument('head', type=argparse.FileType('r'))
  ppop.add_argument('output', type=argparse.FileType('w'))
  ppop.set_defaults(func=pop)
  args = parser.parse_args()
  args.func(args)

if __name__ == '__main__':
  main()
