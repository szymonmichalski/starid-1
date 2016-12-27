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

imgndx = 2
label = labels[imgndx]
image = images[imgndx,:,:,0]
image = tf.cast(image, tf.float32) * (1. / 255) - 0.5
image = tf.reshape(image, [28, 28, 1])

softmax = gn.inference(image)
saver = tf.train.Saver()

with tf.Session() as sess:
  ckpt = tf.train.get_checkpoint_state(FLAGS.checkpoint_dir)
  saver.restore(sess, ckpt.model_checkpoint_path)
  softmaxval = sess.run(softmax)
  print(softmaxval)

