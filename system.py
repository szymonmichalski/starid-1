import subprocess
import lb
import re
import time
import numpy as np

resultscnt = 15
results = np.zeros(shape=(resultscnt, 5), dtype=float)

for resndx in range(0, resultscnt):
  starndx = 800 * (np.mod(resndx, 10) + 1)
  results[resndx, 0] = starndx

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

  # print('%4.0f, %1.0f, %1.0f, %4.3f, %4.3f' % (results[resndx, 0], results[resndx, 1], results[resndx, 3], results[resndx, 2], results[resndx, 4]))

print()
print('%5s  %5s  %5s' % ('n %i' % resultscnt, 'ok', 't'))
print('%5s  %5s  %5s' % ('-----', '-----', '-----'))
print('%5s  %4.3f  %4.3f' % ('lb', np.mean(results[:,1]), np.mean(results[:,2])))
print('%5s  %4.3f  %4.3f' % ('rb', np.mean(results[:,3]), np.mean(results[:,4])))
