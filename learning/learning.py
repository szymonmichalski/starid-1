import numpy as np
import mnist_to_tfrecords

images = mnist_to_tfrecords.read_images('/home/noah/dev/starid/data/mnist/starid_imagesb.mnist')
labels = mnist_to_tfrecords.read_labels('/home/noah/dev/starid/data/mnist/starid_labelsb.mnist')

print (np.array_str(images[0,:,:,0], max_line_width=500))

starndxs = 800 * (labels + 1)
print (np.array_str(starndxs[0:25], max_line_width=500))


