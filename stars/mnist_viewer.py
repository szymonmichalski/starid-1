import matplotlib.pyplot as plt

from stars import mnist_to_tfrecords

imgndx = 13

images = mnist_to_tfrecords.read_images('/home/noah/dev/starid/data/images_b1.mnist')
image = -1 * images[imgndx,:,:,0]

plt.matshow(image, cmap='Greys',  interpolation='nearest')
plt.show()
