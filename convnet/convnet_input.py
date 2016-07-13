import os.path
import time

import numpy
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import mnist

TRAIN_FILE = 'train.tfrecords'

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
  image.set_shape([mnist.IMAGE_PIXELS])
  image = tf.cast(image, tf.float32) * (1. / 255) - 0.5
  label = tf.cast(features['label'], tf.int32)

  return image, label

def inputs(batch_size):
  train = True
  num_epochs = 1
  if not num_epochs: num_epochs = None
  filename = os.path.join('/home/noah/dev/tf/data',
                          TRAIN_FILE if train else VALIDATION_FILE)

  with tf.name_scope('input'):
    filename_queue = tf.train.string_input_producer(
      [filename], num_epochs=num_epochs)
    image, label = read_and_decode(filename_queue)
    images, sparse_labels = tf.train.shuffle_batch(
      [image, label], batch_size=batch_size, num_threads=2,
      capacity=1000 + 3 * batch_size,
      min_after_dequeue=1000)

    return images, sparse_labels
