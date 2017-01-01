import subprocess
import lb
import re
import time

starndx = 800

t1 = time.time()
starndx1 = lb.identifyCentralStar(starndx)
print('lb %.3f ' % float(time.time() - t1))

t1 = time.time()
out = subprocess.check_output(['/home/noah/dev/starid/rules-based/rb', '-s%d' % starndx])
starndx2 = int(re.search(r'identification (\d+)', out.decode('utf-8')).group(1))
print('rb %.3f ' % float(time.time() - t1))

print('true identity %d' % starndx)
print('learning-based identification %d' % starndx1)
print('rules-based identification %d' % starndx2)
