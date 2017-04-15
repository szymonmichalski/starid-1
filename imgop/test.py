import tensorflow as tf

imgop = tf.load_op_library('libimgop.so')
with tf.Session(''):
  out = imgop.star_images_and_labels([[1, 2], [3, 4]]).eval()
print(out)
