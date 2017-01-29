from optparse import OptionParser
import os
import re

def commenter(filename):
  base, suffix = os.path.splitext(filename)
  p = ''
  f = open(filename, 'r')
  for line in f:
    m1 = re.search('/// (.*)', line)
    m2 = re.search('///', line)
    m3 = re.search('### (.*)', line)
    m4 = re.search('###', line)
    if m1:
      p += '%s\n' % str(m1.group(1))
      continue
    if m3:
      p += '%s\n' % str(m3.group(1))
      continue
    if m2:
      p += '\n'
      continue
    if m4:
      p += '\n'
      continue

  return p

def main():
  usage = "usage: %commenter [options] arg"
  parser = OptionParser(usage)
  # parser.add_option('-s', '--starndx', dest='starndx', help='')
  (options, args) = parser.parse_args()
  commenter()

if __name__ == "__main__":
  main()