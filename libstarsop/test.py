import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt

libstarsop = tf.load_op_library('libstarsop.so')
with tf.Session(''):
    image = libstarsop.stars_op(np.zeros(shape=(28, 28))).eval()
plt.matshow(-1 * image, cmap='Greys', interpolation='nearest')
plt.show()
