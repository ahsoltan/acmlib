# TODO:
# Actual error reporting
# Hashing?
# Includes?

import re, os, argparse

def escape(s):
  # Escape `...` => \src{...}
  s = re.sub(r'`([^`]*)`', r'\\src{\1}', s)

  # Escape O(...) => \bigo{...}
  t = ''
  st = []
  i = 0
  while i < len(s):
    if i < len(s) - 1 and s[i:i+2] == 'O(':
      st.append(True)
      t += r'\bigo{'
      i += 2
      continue
    if s[i] == ')':
      assert(len(st) > 0)
      b = st.pop()
      t += '}' if b else ')'
      i += 1
      continue
    t += s[i]
    if s[i] == '(':
      st.append(False)
    i += 1
  assert(len(st) == 0)
  return t

def write_title(f, s):
  f.write(f'\\ctitle{{{s}}}')

def write_header(f, name, s):
  f.write(f'\\cheader{{{name}}}{{{s}}}')

def write_separator(f):
  f.write('\\smallskip\n\\hrule\n')

def write_code(f, lang, s):
  f.write(f'\\begin{{lstlisting}}[language={lang}]\n{s}\\end{{lstlisting}}')

def process(fin, fout, lang):
  s = fin.read()
  code = s.strip()
  m = {}

  # Parse comment
  if s.startswith('/**'):
    headers = ['Opis', 'Stosowanie', 'Czas']
    now = ''
    lines = s.split('\n')
    for i in range(1, len(lines)):
      if lines[i].startswith(' * '):
        line = lines[i][3:]
        for x in headers:
          if line.startswith(x + ': '):
            now = x
            line = line[(len(x) + 2):]
            break
        assert(now != '')
        if now in m:
          m[now] += '\n' + line
        else:
          m[now] = line
      else:
        assert(lines[i].find('*/') != -1)
        break
    end = s.find('*/')
    assert(end != -1)
    code = s[(end + 2):].strip()

  # Verify column width
  limit = 63
  for line in code.split('\n'):
    if len(line) > limit:
      assert(False)

  # Write to file
  write_title(fout, os.path.basename(fin.name))
  for key, val in m.items():
    write_header(fout, key, escape(val))
  write_separator(fout)
  write_code(fout, lang, code)

def main():
  parser = argparse.ArgumentParser()
  parser.add_argument('file', type=argparse.FileType('r'))
  parser.add_argument('lang', choices=['C++', 'bash', 'make', 'raw'])
  parser.add_argument('out', type=argparse.FileType('w'))
  args = parser.parse_args()
  process(args.file, args.out, args.lang)
  args.out.close()

if __name__ == '__main__':
  main()
