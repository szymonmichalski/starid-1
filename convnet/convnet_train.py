import time
import numpy as np
import tensorflow as tf
import convnet
from convnet_input import inputs

flags = tf.app.flags
FLAGS = flags.FLAGS
flags.DEFINE_integer('num_epochs', 2, 'Number of epochs to run trainer.')
flags.DEFINE_integer('batch_size', 100, 'Batch size.')

def run_training():
  with tf.Graph().as_default():
    images, labels = inputs(train=True, batch_size=FLAGS.batch_size,
                            num_epochs=FLAGS.num_epochs)

    logits = convnet.inference(images)
    loss = convnet.loss(logits, labels)
    train_op = convnet.train(loss)

    init_op = tf.initialize_all_variables()
    sess = tf.Session()
    sess.run(init_op)

    coord = tf.train.Coordinator()
    threads = tf.train.start_queue_runners(sess=sess, coord=coord)

    try:
      step = 0
      while not coord.should_stop():
        start_time = time.time()

        _, loss_value = sess.run([train_op, loss])

        duration = time.time() - start_time
        if step % 100 == 0:
          print('Step %d: loss = %.2f (%.3f sec)' % (step, loss_value,
                                                     duration))
        step += 1
    except tf.errors.OutOfRangeError:
      print('Done training for %d epochs, %d steps.' % (FLAGS.num_epochs, step))
    finally:
      coord.request_stop()

    coord.join(threads)
    sess.close()

def main(argv=None):
  run_training()

if __name__ == '__main__':
  tf.app.run()
