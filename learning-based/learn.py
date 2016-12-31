from datetime import datetime
import time
import tensorflow as tf
import tfrecords as tr
import graph as gn
FLAGS = tf.app.flags.FLAGS
tf.app.flags.DEFINE_string('checkpoint_dir', '/home/noah/dev/starid/checkpoint', '')
tf.app.flags.DEFINE_string('ckpt', '/home/noah/dev/starid/checkpoint/model.ckpt', '')
tf.app.flags.DEFINE_string('examples', '/home/noah/dev/starid/data/images_a.tfrecords', '')
tf.app.flags.DEFINE_string('num_examples', 60000, '')
tf.app.flags.DEFINE_integer('batch_size', 100, '')
tf.app.flags.DEFINE_integer('max_steps', 599, '')

# noah@noah:~/dev/starid$ tensorboard --logdir=checkpoint &
def learn():

  images, labels = tr.inputs(FLAGS)
  softmax = gn.inference(images)
  cross_entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(softmax, labels)
  cost = tf.reduce_mean(cross_entropy)
  learning = tf.train.AdamOptimizer(1e-4).minimize(cost)

  init = tf.global_variables_initializer()
  img = tf.summary.image('test', images)
  saver = tf.train.Saver()
  sess = tf.Session()
  sess.run(init)
  summary = tf.summary.merge_all()
  summary_writer = tf.summary.FileWriter(FLAGS.checkpoint_dir, sess.graph)
  tf.train.start_queue_runners(sess=sess)
  for step in range(FLAGS.max_steps):
    start_time = time.time()
    _, cost_value, img_summary = sess.run([learning, cost, img])
    duration = time.time() - start_time
    if step % 10 == 0:
      num_examples_per_step = FLAGS.batch_size
      examples_per_sec = num_examples_per_step / duration
      sec_per_batch = float(duration)
      format_str = ('%s: step %d, loss = %.2f (%.1f examples/sec; %.3f sec/batch)')
      print (format_str % (datetime.now(), step, cost_value, examples_per_sec, sec_per_batch))
    if step % 100 == 0:
      summary_str = sess.run(summary)
      summary_writer.add_summary(summary_str, step)
      summary_writer.add_summary(img_summary)
  saver.save(sess, FLAGS.ckpt)

learn()

