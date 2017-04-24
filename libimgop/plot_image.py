import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt

libimgop = tf.load_op_library('libimgop.so')
with tf.Session(''):
    image = libimgop.image(np.zeros(shape=(28, 28))).eval()
plt.matshow(-1 * image, cmap='Greys', interpolation='nearest')
plt.show()
