import tensorflow as tf

FLAGS = tf.app.flags.FLAGS
IMAGE_SIZE = 28
NUM_CLASSES = 10
NUM_EXAMPLES_PER_EPOCH_FOR_TRAIN = 60000
NUM_EXAMPLES_PER_EPOCH_FOR_EVAL = 10000

def get_example(filename_queue):
  class Example(object):
    pass

  ##############################################################
  # intput example from file
  reader = tf.TFRecordReader()
  _, record = reader.read(filename_queue)
  features = tf.parse_single_example(record,
    features={
      'height': tf.FixedLenFeature([], tf.int64),
      'width': tf.FixedLenFeature([], tf.int64),
      'depth': tf.FixedLenFeature([], tf.int64),
      'label': tf.FixedLenFeature([], tf.int64),
      'image_raw': tf.FixedLenFeature([], tf.string),
    })
  ##############################################################

  example = Example()
  example.height = tf.cast(features['height'], tf.int32)
  example.width = tf.cast(features['width'], tf.int32)
  example.depth = tf.cast(features['depth'], tf.int32)
  example.label = tf.cast(features['label'], tf.int32)
  image = tf.decode_raw(features['image_raw'], tf.uint8)
  image.set_shape([IMAGE_SIZE * IMAGE_SIZE])
  image = tf.cast(image, tf.float32) * (1. / 255) - 0.5
  example.image = tf.reshape(image, [IMAGE_SIZE, IMAGE_SIZE, 1])
  return example

def get_batch(example, min_queue_examples, batch_size, shuffle):
  num_preprocess_threads = 2
  if shuffle:
    images, labels = tf.train.shuffle_batch(
      [example.image, example.label],
      batch_size=batch_size,
      num_threads=num_preprocess_threads,
      capacity=min_queue_examples + 3 * batch_size,
      min_after_dequeue=min_queue_examples)
  else:
    images, labels = tf.train.batch(
      [example.image, example.label],
      batch_size=batch_size,
      num_threads=num_preprocess_threads,
      capacity=min_queue_examples + 3 * batch_size)
  tf.image_summary('images', images)
  return images, tf.reshape(labels, [batch_size])

def inputs(filename, batch_size):
  filenames = [filename]
  num_examples_per_epoch = NUM_EXAMPLES_PER_EPOCH_FOR_TRAIN
  filename_queue = tf.train.string_input_producer(filenames)
  example = get_example(filename_queue)
  min_queue_examples = int(0.4 * num_examples_per_epoch)
  images, labels = get_batch(example, min_queue_examples, batch_size, shuffle=False)
  return images, labels
