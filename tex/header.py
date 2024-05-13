import argparse

def push(args):
  args.output.write(f'{args.caption}\n')
  args.output.close()

def pop(args):
  seg = args.data.split(';')
  if not seg[0]:
    return
  lines = [x.strip() for x in args.input.readlines()]
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

  push_parser = subparsers.add_parser('push')
  push_parser.add_argument('caption', type=str)
  push_parser.add_argument('output', type=argparse.FileType('a'))
  push_parser.set_defaults(func=push)

  pop_parser = subparsers.add_parser('pop')
  pop_parser.add_argument('data', type=str)
  pop_parser.add_argument('input', type=argparse.FileType('r'))
  pop_parser.add_argument('output', type=argparse.FileType('w'))
  pop_parser.set_defaults(func=pop)

  args = parser.parse_args()
  args.func(args)
  pass

if __name__ == '__main__':
  main()
