### *starid*
###
### test and demo
###

import matplotlib.pyplot as plt
import libstarid.libstarid as ls
libstarid = ls.libstarid()
libstarid.load_pairs()

image = libstarid.image(starndx=13)
starndx = libstarid.id(image)

plt.matshow(-1 * image, cmap='Greys', interpolation='nearest')
plt.show()

