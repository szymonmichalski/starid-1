from datetime import datetime
import math
import numpy as np
import tensorflow as tf
import tfrecords as tr
import graph as gn
FLAGS = tf.app.flags.FLAGS
tf.app.flags.DEFINE_string('checkpoint_dir', '/home/noah/dev/starid/checkpoint', '')
tf.app.flags.DEFINE_string('examples', '/home/noah/dev/starid/data/images_b.tfrecords', '')
tf.app.flags.DEFINE_string('num_examples', 10000, '')
tf.app.flags.DEFINE_string('batch_size', 100, '')
tf.app.flags.DEFINE_integer('max_steps', 99, '')

images, labels = tr.inputs(FLAGS)
softmax = gn.inference(images)
prediction = tf.nn.in_top_k(softmax, labels, 1)

saver = tf.train.Saver()
ckpt = tf.train.get_checkpoint_state(FLAGS.checkpoint_dir)
sess = tf.Session()
saver.restore(sess, ckpt.model_checkpoint_path)

coord = tf.train.Coordinator()
threads = []
for qr in tf.get_collection(tf.GraphKeys.QUEUE_RUNNERS):
  threads.extend(qr.create_threads(sess, coord=coord, daemon=True, start=True))
goodcnt = 0
for step in range(FLAGS.max_steps):
  predictions = sess.run([prediction])
  goodcnt += np.sum(predictions)
precision = goodcnt / FLAGS.num_examples
print('%s: precision @ 1 = %.3f' % (datetime.now(), precision))
coord.request_stop()
coord.join(threads, stop_grace_period_secs=10)
