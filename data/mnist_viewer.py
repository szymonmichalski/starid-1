from data import mnist_to_tfrecords
import numpy as np
import matplotlib.pyplot as plt

imgndx = 21

images = mnist_to_tfrecords.read_images('/home/noah/dev/starid/data/images_b1.mnist')
image = images[imgndx,:,:,0]
# image = tf.cast(image, tf.float32) * (1. / 255) - 0.5
# image = tf.reshape(image, [28, 28, 1])

plt.imshow(image)
plt.show()
