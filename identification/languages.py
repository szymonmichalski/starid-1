import numpy as np
import matplotlib.pyplot as plt
np.set_printoptions(linewidth=200)

import libstarid.libstarid as ls
libstarid = ls.libstarid()

def image_info_to_image(image_info):
    image = np.zeros((28,28))
    for rowndx in range(len(image_info)):
        image[int(image_info[rowndx,0]), int(image_info[rowndx,1])] = 1.0
    return image

image_info = libstarid.image_info(starndx=3)
print(image_info)

image = image_info_to_image(image_info)
plt.matshow(-1 * image, cmap='Greys', interpolation='nearest')
plt.show()
