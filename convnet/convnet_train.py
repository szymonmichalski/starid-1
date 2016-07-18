from datetime import datetime
import os.path
import time
from six.moves import xrange

import numpy as np
import tensorflow as tf

import convnet
from convnet_input import inputs

FLAGS = tf.app.flags.FLAGS
tf.app.flags.DEFINE_string('train_dir', '/home/noah/dev/train1', 'event dir')
tf.app.flags.DEFINE_integer('max_steps', 590, 'number of batches to run')
tf.app.flags.DEFINE_integer('batch_size', 100, 'batch size')

def run_training():
  with tf.Graph().as_default():

    images, labels = inputs(FLAGS.batch_size)
    logits = convnet.inference(images)
    loss = convnet.loss(logits, labels)
    train_op = convnet.train(loss)

    init = tf.initialize_all_variables()
    sess = tf.Session()
    sess.run(init)
    summary_op = tf.merge_all_summaries()
    summary_writer = tf.train.SummaryWriter(FLAGS.train_dir, sess.graph)
    tf.train.start_queue_runners(sess=sess)

    for step in xrange(FLAGS.max_steps):
      start_time = time.time()
      _, loss_value = sess.run([train_op, loss])
      duration = time.time() - start_time

      if step % 10 == 0:
        num_examples_per_step = FLAGS.batch_size
        examples_per_sec = num_examples_per_step / duration
        sec_per_batch = float(duration)
        format_str = ('%s: step %d, loss = %.2f (%.1f examples/sec; %.3f sec/batch)')
        print (format_str % (datetime.now(), step, loss_value, examples_per_sec, sec_per_batch))

      if step % 100 == 0:
        summary_str = sess.run(summary_op)
        summary_writer.add_summary(summary_str, step)

def main(argv=None):
  if tf.gfile.Exists(FLAGS.train_dir):
    tf.gfile.DeleteRecursively(FLAGS.train_dir)
  tf.gfile.MakeDirs(FLAGS.train_dir)
  run_training()

if __name__ == '__main__':
  tf.app.run()
