import tensorflow as tf
import numpy as nd
import matplotlib.pyplot as plt

imgmat1 = nd.zeros(shape=(28,28))

imgop = tf.load_op_library('libimgop.so')
with tf.Session(''):
  imgmat2 = imgop.star_images_and_labels(imgmat1).eval()
print(imgmat2)

plt.matshow(-1*imgmat2, cmap='Greys', interpolation='nearest')
plt.show()