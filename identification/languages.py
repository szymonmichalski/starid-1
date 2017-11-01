import numpy as np
import matplotlib.pyplot as plt
import languages_starimg
import libstarid.libstarid as ls
libstarid = ls.libstarid()

image_info = libstarid.image_info(starndx=3)
starimg = languages_starimg.languages_starimg(image_info)

starimg.print_image_info()
plt.matshow(-1 * starimg.image, cmap='Greys', interpolation='nearest')
plt.show()
