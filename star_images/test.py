import tensorflow as tf
test_module = tf.load_op_library('libstar_images.so')
with tf.Session(''):
  test_module.zero_out([[1, 2], [3, 4]]).eval()

# Prints
array([[1, 0], [0, 0]], dtype=int32)