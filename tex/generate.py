from process import *
import argparse
import os

def write(out, caption, head, file, lang):
  out.append(r'\ctitle{%s}' % caption)
  for key, val in file.headers.items():
    out.append(r'\cheader{%s}{%s}' % (key, escape(val)))
  # TODO: handle includes
  out.append(r'\smallskip')
  out.append(r'\hrule')
  out.append(r'\marks\hdrmark{%s}' % head)
  out.append(r'\begin{lstlisting}[language=%s]' % lang)
  out.append(file.source)
  out.append(r'\end{lstlisting}')

def tex(args):
  caption = os.path.basename(args.input.name)
  head = os.path.splitext(caption)[0]
  args.head.write(f'{head}\n')
  args.head.close()
  try:
    if args.lang == 'C++' or args.lang == 'Python':
      file = process_with_comments(args.input)
    else: 
      file = process_raw(args.input)
    lines = []
    write(lines, caption, head, file, args.lang)
    if file.warnings:
      args.output.write(r'\acmwarning{%s}' % file.warnings)
    args.output.write('\n'.join(lines))
  except FileError as e:
    args.output.write(r'\acmerror{%s}' % str(e))
  args.output.close()

def hdr(args): 
  seg = args.data.split(';')
  lines = [x.strip() for x in args.head.readlines()]
  first = lines.index(seg[0])
  last = lines.index(seg[1]) if seg[1] else len(lines) - 1
  sub = lines[first:last + 1]
  length = len(''.join(sub))
  font_size = 10 if length <= 150 else 8
  f = args.output
  f.write(r'\fontsize{%s}{%s}\textbf{%s}' % (font_size, font_size, r'\enspace{}'.join(sub)))
  f.close()

def main():
  parser = argparse.ArgumentParser()
  subparsers = parser.add_subparsers(required=True)

  ptex = subparsers.add_parser('tex')
  ptex.add_argument('input', type=argparse.FileType('r'))
  ptex.add_argument('lang', choices=['C++', 'Python', 'bash', 'make', 'raw'])
  ptex.add_argument('output', type=argparse.FileType('w'))
  ptex.add_argument('head', type=argparse.FileType('a'))
  ptex.set_defaults(func=tex)

  phdr = subparsers.add_parser('hdr')
  phdr.add_argument('data', type=str)
  phdr.add_argument('head', type=argparse.FileType('r'))
  phdr.add_argument('output', type=argparse.FileType('w'))
  phdr.set_defaults(func=hdr)
  args = parser.parse_args()
  args.func(args)

if __name__ == '__main__':
  main()
