import commenter as co
import datetime

outfile = 'comments.md'
root = '../'

lb = 'learning-based/lb.py'
graph = 'learning-based/graph.py'

rb = 'rules-based/rb.cpp'

with open(outfile, 'w') as f:

  f.write('# learning\n')
  f.write('%s' % co.commenter(root + lb))
  f.write('%s' % co.commenter(root + graph))

  f.write('# heuristics\n')
  p = co.commenter(root + rb)
  f.write('%s' % p)

