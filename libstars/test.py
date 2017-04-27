import libstars
import numpy as np
import matplotlib.pyplot as plt

stars = libstars.libstars()
starndx = 4
image = stars.image(starndx)
plt.matshow(-1 * image, cmap='Greys', interpolation='nearest')
plt.show()