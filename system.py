import subprocess
import lb
import re
import time
import numpy as np

resultscnt = 25
results = np.zeros(shape=(resultscnt, 6), dtype=float)

for resultsndx in range(0, resultscnt):
  starndx = np.mod(resultsndx, 10)
  starsetndx = np.random.randint(0, 1000)
  imgndx = starndx + starsetndx*10
  results[resultsndx, 0] = starndx
  results[resultsndx, 1] = imgndx

  t1 = time.time()
  starndx1 = lb.identifyCentralStar(imgndx)
  if starndx1 == results[resultsndx, 0]:
    results[resultsndx, 2] = 1
  results[resultsndx, 3] = float(time.time() - t1)

  t2 = time.time()
  out = subprocess.check_output(['/home/noah/dev/starid/rules-based/rb', '--imgndx %d' % starndx])
  starndx2 = int(re.search(r'identification (\d+)', out.decode('utf-8')).group(1))
  if starndx2 == results[resultsndx, 0]:
    results[resultsndx, 4] = 1
  results[resultsndx, 5] = float(time.time() - t2)

  print('%5.0f, %5.0f, %1.0f, %1.0f' % (results[resultsndx, 0], results[resultsndx, 1], results[resultsndx, 2], results[resultsndx, 4]))

print()
print('%5s  %5s  %5s' % ('n %i' % resultscnt, 'ok', 't'))
print('%5s  %5s  %5s' % ('-----', '-----', '-----'))
print('%5s  %4.3f  %4.3f' % ('lb', np.mean(results[:,2]), np.mean(results[:,3])))
print('%5s  %4.3f  %4.3f' % ('rb', np.mean(results[:,4]), np.mean(results[:,5])))
