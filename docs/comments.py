import commenter as co
import datetime

outfile     = 'comments.md'
lbroot      = '../learning-based/'
lb          = 'lb.py'
model       = 'model.py'
learning    = 'learning.py'
testing     = 'testing.py'
rbroot      = '../rules-based/'
rb          = 'rb.cpp'
triangles   = 'triangles.h'

with open(outfile, 'w') as f:

  f.write('# learning\n')
  f.write('%s' % co.commenter(lbroot + lb))
  f.write('%s' % co.commenter(lbroot + model))
  f.write('%s' % co.commenter(lbroot + learning))
  f.write('%s' % co.commenter(lbroot + testing))

  f.write('# heuristics\n')
  f.write('%s' % co.commenter(rbroot + rb))
  f.write('%s' % co.commenter(rbroot + triangles))

