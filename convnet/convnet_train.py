from datetime import datetime
import time
import numpy as np
import tensorflow as tf
import convnet

FLAGS = tf.app.flags.FLAGS
tf.app.flags.DEFINE_string('train_dir', '/home/noah/dev/tflog', 'event dir')
tf.app.flags.DEFINE_integer('max_steps', 590, 'number of batches to run')
tf.app.flags.DEFINE_integer('batch_size', 100, 'batch size')
NUM_CLASSES = 10
IMAGE_SIZE = 28
IMAGE_PIXELS = IMAGE_SIZE * IMAGE_SIZE

def read_and_decode(filename_queue):
  reader = tf.TFRecordReader()
  _, serialized_example = reader.read(filename_queue)
  features = tf.parse_single_example(
    serialized_example,
    features={
      'image_raw': tf.FixedLenFeature([], tf.string),
      'label': tf.FixedLenFeature([], tf.int64),
    })
  image = tf.decode_raw(features['image_raw'], tf.uint8)
  image.set_shape([IMAGE_PIXELS])
  label = tf.cast(features['label'], tf.int32)
  image = tf.cast(image, tf.float32) * (1. / 255) - 0.5
  image = tf.reshape(image, [28, 28, 1])
  return image, label

def inputs(batch_size):
  num_epochs = 1
  if not num_epochs: num_epochs = None
  filename = '/home/noah/dev/starid_data/starid_yawedb.tfrecords'
  #filename = '/home/noah/dev/mnist_yawed.tfrecords'
  with tf.name_scope('input'):
    filename_queue = tf.train.string_input_producer(
      [filename], num_epochs=num_epochs)
    image, label = read_and_decode(filename_queue)
    images, sparse_labels = tf.train.shuffle_batch(
      [image, label], batch_size=batch_size, num_threads=2,
      capacity=1000 + 3 * batch_size,
      min_after_dequeue=1000)
    return images, sparse_labels

def run_training():
  with tf.Graph().as_default():

    images, labels = inputs(FLAGS.batch_size)
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

    # for step in range(590):
    for step in range(90):
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
  run_training()

if __name__ == '__main__':
  tf.app.run()
