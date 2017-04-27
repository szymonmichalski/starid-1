import numpy as np
import matplotlib.pyplot as plt

import libstars as ls
libstars = ls.libstars()
libstars.load_pairs()

image = libstars.image(starndx=4)
print(libstars.id(image))

# plt.matshow(-1 * image, cmap='Greys', interpolation='nearest')
# plt.show()
