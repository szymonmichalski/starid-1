### *image viewer*
###
### shows 28 x 28 mnist style star images.
###
import matplotlib.pyplot as plt
import mnist_to_tfrecords

imgndx = 1

images = mnist_to_tfrecords.read_images('/home/noah/starid/stars/adata/eval_examples')
image = -1 * images[imgndx, :, :, 0]

plt.matshow(image, cmap='Greys', interpolation='nearest')
plt.show()