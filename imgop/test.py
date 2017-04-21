import tensorflow as tf
import numpy as nd

imgmat1 = nd.zeros(shape=(28,28))

imgop = tf.load_op_library('libimgop.so')
with tf.Session(''):
  imgmat2 = imgop.star_images_and_labels(imgmat1).eval()
print(imgmat2)
