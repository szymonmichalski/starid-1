import matplotlib.pyplot as plt
import mnist_to_tfrecords

imgndx = 1

images = mnist_to_tfrecords.read_images('/home/noah/starid/stars/data/images_b1.mnist')
image = -1 * images[imgndx,:,:,0]

plt.matshow(image, cmap='Greys',  interpolation='nearest')
plt.show()
