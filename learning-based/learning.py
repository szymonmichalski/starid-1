### **learning**
###
### performs training of the model.
###
import time
import tensorflow as tf
import tfrecords as tr
import model as gn
FLAGS = tf.app.flags.FLAGS
tf.app.flags.DEFINE_string('checkpoint_dir', '/home/noah/dev/starid/models', '')
tf.app.flags.DEFINE_string('ckpt', '/home/noah/dev/starid/models/model.ckpt', '')
tf.app.flags.DEFINE_string('examples', '/home/noah/dev/starid/data/images_a.tfrecords', '')
tf.app.flags.DEFINE_string('num_examples', 60000, '')
tf.app.flags.DEFINE_integer('batch_size', 100, '')
tf.app.flags.DEFINE_integer('max_steps', 600, '')

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
  for batch in range(FLAGS.max_steps):
    t1 = time.time()
    _, costval, img_summary = sess.run([learning, cost, img])
    if batch % 10 == 0:
      print ('b %d, cost %.2f, %.3f s/b' % (batch+10, costval, float(time.time() - t1)))
    if batch % 100 == 0:
      summary_str = sess.run(summary)
      summary_writer.add_summary(summary_str, batch)
      summary_writer.add_summary(img_summary)
  saver.save(sess, FLAGS.ckpt)
learn()

