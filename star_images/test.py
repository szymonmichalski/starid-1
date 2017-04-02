import tensorflow as tf

star_images_module = tf.load_op_library('libstar_images.so')
with tf.Session(''):
  out = star_images_module.star_images([[1, 2], [3, 4]]).eval()
print(out)
