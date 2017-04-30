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

outfile = 'comments.md'
root = '../'
idroot = '../identification/'
starsroot = '../star/'
libstarid = '../libstarid/'

with open(outfile, 'w') as f:
    f.write('%s' % commenter(root + 'starid.py'))

    f.write('%s' % commenter(idroot + 'identification.cpp'))
    f.write('%s' % commenter(idroot + 'triangles.h'))
    f.write('%s' % commenter(idroot + 'triangle.h'))
    f.write('%s' % commenter(idroot + 'triangle_side.h'))
    f.write('%s' % commenter(idroot + 'cnn1.py'))
    f.write('%s' % commenter(idroot + 'cnn2.py'))

    f.write('%s' % commenter(starsroot + 'star.cpp'))
    f.write('%s' % commenter(starsroot + 'sky.h'))
    f.write('%s' % commenter(starsroot + 'pointing_vectors.h'))
    f.write('%s' % commenter(starsroot + 'pairs.h'))
    f.write('%s' % commenter(starsroot + 'float_int_table.h'))
    f.write('%s' % commenter(starsroot + 'globals.h'))
    f.write('%s' % commenter(starsroot + 'star_catalog.h'))

    f.write('%s' % commenter(libstarid + 'libstarid.h'))
