import numpy as np
import mnist
import tensorflow as tf
import tfrecords as tr
import graph_nodes as gn
FLAGS = tf.app.flags.FLAGS
tf.app.flags.DEFINE_string('checkpoint_dir', '/home/noah/dev/train', 'model dir')

images = mnist.read_images('/home/noah/dev/starid/data/images_b1.mnist')
labels = mnist.read_labels('/home/noah/dev/starid/data/images_b2.mnist')
starndxs = 800 * (labels + 1)
# print (np.array_str(images[0,:,:,0], max_line_width=500))
# print (np.array_str(starndxs[0:25], max_line_width=500))

label = labels[0]
image = images[0,:,:,0]
# image.set_shape([28*28])
# image = tf.cast(image, tf.float32) * (1. / 255) - 0.5
class Example(object):
  pass
example = Example()
example.height = tf.cast(28, tf.int32)
example.width = tf.cast(28, tf.int32)
example.depth = tf.cast(1, tf.int32)
example.label = tf.cast(label, tf.int32)
example.image = tf.cast(image, tf.float32) * (1. / 255) - 0.5
images, labels = tr.get_batch(example, min_queue_examples=1, batch_size=1, shuffle=False)

softmax = gn.inference(images)
top_k_op = tf.nn.in_top_k(softmax, labels, 1)
saver = tf.train.Saver()
with tf.Session() as sess:
  ckpt = tf.train.get_checkpoint_state(FLAGS.checkpoint_dir)
  saver.restore(sess, ckpt.model_checkpoint_path)
  coord = tf.train.Coordinator()
  predictions = sess.run([top_k_op])
  print(np.sum(predictions))
  coord.request_stop()

