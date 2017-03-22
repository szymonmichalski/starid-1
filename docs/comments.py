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

outfile         = 'comments.md'

lbroot          = '../learning-based/'
lb              = 'lb.py'
model           = 'model.py'
learning        = 'learning.py'
testing         = 'testing.py'

rbroot          = '../rules-based/'
rb              = 'rb.cpp'
star_identifier = 'star_identifier.h'
triangle        = 'triangle.h'
triangle_side   = 'triangle_side.h'
pairs           = 'pairs_over_whole_sky.h'

with open(outfile, 'w') as f:

  # f.write('**learning**\n')
  f.write('%s' % commenter(lbroot + lb))
  f.write('%s' % commenter(lbroot + model))
  f.write('%s' % commenter(lbroot + learning))
  f.write('%s' % commenter(lbroot + testing))

  # f.write('**heuristics**\n')
  f.write('%s' % commenter(rbroot + rb))
  f.write('%s' % commenter(rbroot + star_identifier))
  f.write('%s' % commenter(rbroot + triangle))
  f.write('%s' % commenter(rbroot + triangle_side))
  f.write('%s' % commenter(rbroot + pairs))

