import subprocess
import lb
import re

starndx = 800

starndx1 = lb.identifyCentralStarInImage(starndx)

out = subprocess.check_output(['/home/noah/dev/starid/rules-based/rb', '-s%d' % starndx])
starndx2 = int(re.search(r'identification (\d+)', out.decode('utf-8')).group(1))

print('true identity %d' % starndx)
print('learning-based identification %d' % starndx1)
print('rules-based identification %d' % starndx2)
