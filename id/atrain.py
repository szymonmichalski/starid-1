### *training*
###
### performs training of the model.
###
import time
import tensorflow as tf
import amodel
import acontainer_read

FLAGS = tf.app.flags.FLAGS
tf.app.flags.DEFINE_string('checkpoint_dir', '/home/noah/starid/id1/adata', '')
tf.app.flags.DEFINE_string('ckpt', '/home/noah/starid/id1/adata/model.ckpt', '')
tf.app.flags.DEFINE_string('examples', '/home/noah/starid/stars/data/train', '')
tf.app.flags.DEFINE_string('num_examples', 60000, '')
tf.app.flags.DEFINE_integer('batch_size', 100, '')
tf.app.flags.DEFINE_integer('max_steps', 600, '')


def train():
    images, labels = acontainer_read.inputs(FLAGS)
    softmax = amodel.inference(images)
    cross_entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(logits=softmax, labels=labels)
    loss = tf.reduce_mean(cross_entropy)
    train_op = tf.train.AdamOptimizer(1e-4).minimize(loss)

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
        _, lossval, img_summary = sess.run([train_op, loss, img])
        if batch % 10 == 0:
            print('b %d, cost %.2f, %.3f s/b' % (batch + 10, lossval, float(time.time() - t1)))
        if batch % 100 == 0:
            summary_str = sess.run(summary)
            summary_writer.add_summary(summary_str, batch)
            summary_writer.add_summary(img_summary)
    saver.save(sess, FLAGS.ckpt)


train()
