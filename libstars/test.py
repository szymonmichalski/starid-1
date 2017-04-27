import numpy as np
import matplotlib.pyplot as plt

import libstars
stars = libstars.libstars()
starndx = 4
image = stars.image(starndx)
plt.matshow(-1 * image, cmap='Greys', interpolation='nearest')
plt.show()