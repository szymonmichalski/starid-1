import numpy as np
import matplotlib.pyplot as plt

import libstars
stars = libstars.libstars()
image = stars.image(starndx=4)
# plt.matshow(-1 * image, cmap='Greys', interpolation='nearest')
# plt.show()

stars.load_pairs()
print(stars.id(image))
