import numpy as np
import mnist
import tensorflow as tf
import graph_nodes as gn
FLAGS = tf.app.flags.FLAGS
tf.app.flags.DEFINE_string('checkpoint_dir', '/home/noah/dev/train', 'model dir')

images = mnist.read_images('/home/noah/dev/starid/data/images_b1.mnist')
labels = mnist.read_labels('/home/noah/dev/starid/data/images_b2.mnist')
print (np.array_str(images[0,:,:,0], max_line_width=500))
starndxs = 800 * (labels + 1)
print (np.array_str(starndxs[0:25], max_line_width=500))

# images, labels = gn.inputs_eval()
softmax = gn.inference(images)
top_k_op = tf.nn.in_top_k(softmax, labels, 1)
# saver = tf.train.Saver()
with tf.Session() as sess:
  ckpt = tf.train.get_checkpoint_state(FLAGS.checkpoint_dir)
  # saver.restore(sess, ckpt.model_checkpoint_path)
  predictions = sess.run([top_k_op])
print(np.sum(predictions))

