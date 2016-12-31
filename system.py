import subprocess
import lb

starndx = 800
starndx1 = lb.identifyCentralStarInImage(starndx)
starndx2 = int(subprocess.check_output([ '/home/noah/dev/starid/rules-based/rb', '-s%d' % starndx ]))

print('true identity %d' % starndx)
print('learning-based identification %d' % starndx1)
print('rules-based identification %d' % starndx2)
