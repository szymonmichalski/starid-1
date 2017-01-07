import subprocess
import lb
import re
import time
import numpy as np

results = np.zeros(shape=(10, 5), dtype=float)

for resndx in range(0,10):
  results[resndx, 0] = 800*(resndx+1) # starndx

  t1 = time.time()
  starndx1 = lb.identifyCentralStar(results[resndx,0])
  if starndx1 == results[resndx,0]:
    results[resndx,1] = 1
  results[resndx,2] = float(time.time() - t1)

  t2 = time.time()
  out = subprocess.check_output(['/home/noah/dev/starid/rules-based/rb', '-s%d' % results[resndx,0]])
  starndx2 = int(re.search(r'identification (\d+)', out.decode('utf-8')).group(1))
  if starndx2 == results[resndx, 0]:
    results[resndx, 3] = 1
  results[resndx,4] = float(time.time() - t2)

  print('%4.0f, %1.0f, %1.0f, %4.3f, %4.3f' % (results[resndx, 0], results[resndx, 1], results[resndx, 3],
                                          results[resndx, 2], results[resndx, 4]))

print()
print('    %4s  %4s' % ('ok  ', 't    '))
print('--  %4s  %4s' % ('----', '-----'))
print('lb  %4.2f  %4.3f' % (np.mean(results[:,1]), np.mean(results[:,2])))
print('rb  %4.2f  %4.3f' % (np.mean(results[:,3]), np.mean(results[:,4])))
