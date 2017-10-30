import numpy as np
import matplotlib.pyplot as plt

import libstarid as ls
libstarid = ls.libstarid()
# libstarid.load_pairs()

# starndx 3 has been used for many example images
image = libstarid.image(starndx=3)
# print(libstarid.id(image))

angseq = libstarid.ang_seq_vec(starndx=3)
# print(angseq)

plt.matshow(-1 * image, cmap='Greys', interpolation='nearest')
plt.show()
