from datetime import datetime
import time
import numpy as np
import os
import tensorflow as tf
import convnet
FLAGS = tf.app.flags.FLAGS
tf.app.flags.DEFINE_string('train_dir', '/home/noah/dev/train_dir', 'event dir')
tf.app.flags.DEFINE_integer('max_steps', 590, 'number of batches to run')

def train():
  with tf.Graph().as_default():
    global_step = tf.Variable(0, trainable=False)

    images, labels = convnet.inputs_train()
    softmax = convnet.inference(images)
    loss = convnet.loss(softmax, labels)
    train_op = convnet.train(loss)
    init_op = tf.initialize_all_variables()
    img_op = tf.image_summary('test', images, max_images=10)

    sess = tf.Session()
    sess.run(init_op)
    summary_op = tf.merge_all_summaries()
    summary_writer = tf.train.SummaryWriter(FLAGS.train_dir, sess.graph)
    tf.train.start_queue_runners(sess=sess)

    for step in range(590):
      start_time = time.time()

      _, loss_value, img_summary = sess.run([train_op, loss, img_op])

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
        summary_writer.add_summary(img_summary)

def main(argv=None):
  if tf.gfile.Exists(FLAGS.train_dir):
    tf.gfile.DeleteRecursively(FLAGS.train_dir)
  tf.gfile.MakeDirs(FLAGS.train_dir)
  train()

if __name__ == '__main__':
  tf.app.run()
