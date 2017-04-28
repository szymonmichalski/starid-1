import numpy as np
import matplotlib.pyplot as plt

import libstarid as ls
libstarid = ls.libstarid()
libstarid.load_pairs()

image = libstarid.image(starndx=4)
print(libstarid.id(image))

plt.matshow(-1 * image, cmap='Greys', interpolation='nearest')
plt.show()
