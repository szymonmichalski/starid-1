import commenter as co
import datetime

outfile = 'comments.md'
root = '../'

lb = 'learning-based/lb.py'
model = 'learning-based/model.py'
learning = 'learning-based/learning.py'
testing = 'learning-based/testing.py'

rb = 'rules-based/rb.cpp'

with open(outfile, 'w') as f:

  f.write('# learning\n')
  f.write('%s' % co.commenter(root + lb))
  f.write('%s' % co.commenter(root + model))
  f.write('%s' % co.commenter(root + learning))
  f.write('%s' % co.commenter(root + testing))

  f.write('# heuristics\n')
  p = co.commenter(root + rb)
  f.write('%s' % p)

