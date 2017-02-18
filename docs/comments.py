import commenter as co
import datetime

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

  f.write('# learning\n')
  f.write('%s' % co.commenter(lbroot + lb))
  f.write('%s' % co.commenter(lbroot + model))
  f.write('%s' % co.commenter(lbroot + learning))
  f.write('%s' % co.commenter(lbroot + testing))

  f.write('# heuristics\n')
  f.write('%s' % co.commenter(rbroot + rb))
  f.write('%s' % co.commenter(rbroot + star_identifier))
  f.write('%s' % co.commenter(rbroot + triangle))
  f.write('%s' % co.commenter(rbroot + triangle_side))
  f.write('%s' % co.commenter(rbroot + pairs))

