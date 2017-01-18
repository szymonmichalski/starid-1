from data import mnist_to_tfrecords
import numpy as np
import matplotlib.pyplot as plt

imgndx = 12

images = mnist_to_tfrecords.read_images('/home/noah/dev/starid/data/images_b1.mnist')
image = -1 * images[imgndx,:,:,0]

plt.matshow(image, cmap='Greys',  interpolation='nearest')
plt.show()
