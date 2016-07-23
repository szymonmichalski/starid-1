from tensorflow.python.platform import gfile
import numpy
import tensorflow as tf

tf.app.flags.DEFINE_string('directory', '/home/noah/dev', 'dir')
FLAGS = tf.app.flags.FLAGS

def _int64_feature(value):
  return tf.train.Feature(int64_list=tf.train.Int64List(value=[value]))

def _bytes_feature(value):
  return tf.train.Feature(bytes_list=tf.train.BytesList(value=[value]))
def _read32(bytestream):
  dt = numpy.dtype(numpy.uint32).newbyteorder('>')
  return numpy.frombuffer(bytestream.read(4), dtype=dt)[0]

def read_images(filename):
  with gfile.Open(filename, 'rb') as bytestream:
    magic = _read32(bytestream)
    if magic != 2051:
      raise ValueError('magic number error %s' % (magic, filename))
    num_images = _read32(bytestream)
    rows = _read32(bytestream)
    cols = _read32(bytestream)
    buf = bytestream.read(rows * cols * num_images)
    data = numpy.frombuffer(buf, dtype=numpy.uint8)
    data = data.reshape(num_images, rows, cols, 1)
    return data

def read_labels(filename, one_hot=False, num_classes=10):
  with gfile.Open(filename, 'rb') as bytestream:
    magic = _read32(bytestream)
    if magic != 2049:
      raise ValueError('magic number error %s' % (magic, filename))
    num_items = _read32(bytestream)
    buf = bytestream.read(num_items)
    labels = numpy.frombuffer(buf, dtype=numpy.uint8)
    if one_hot:
      return dense_to_one_hot(labels, num_classes)
    return labels

def dense_to_one_hot(labels_dense, num_classes):
  num_labels = labels_dense.shape[0]
  index_offset = numpy.arange(num_labels) * num_classes
  labels_one_hot = numpy.zeros((num_labels, num_classes))
  labels_one_hot.flat[index_offset + labels_dense.ravel()] = 1
  return labels_one_hot

def convert_to_tfrecords(images, labels, filename):
  num_examples = labels.shape[0]
  if images.shape[0] != num_examples:
    raise ValueError("%d error %d." % (images.shape[0], num_examples))
  rows = images.shape[1]
  cols = images.shape[2]
  depth = images.shape[3]
  writer = tf.python_io.TFRecordWriter(filename)
  for index in range(num_examples):
    image_raw = images[index].tostring()
    example = tf.train.Example(features=tf.train.Features(feature={
        'height': _int64_feature(rows),
        'width': _int64_feature(cols),
        'depth': _int64_feature(depth),
        'label': _int64_feature(int(labels[index])),
        'image_raw': _bytes_feature(image_raw)}))
    writer.write(example.SerializeToString())
  writer.close()

def main(argv):
  images = read_images('/home/noah/dev/mnist_yawed_images.mnist')
  labels = read_labels('/home/noah/dev/mnist_yawed_labels.mnist')
  convert_to_tfrecords(images, labels, '/home/noah/dev/mnist_yawed.tfrecords')
  # images = read_images('/home/noah/dev/mnist_unyawed_images.mnist')
  # labels = read_labels('/home/noah/dev/mnist_unyawed_labels.mnist')
  # convert_to_tfrecords(images, labels, '/home/noah/dev/mnist_unyawed.tfrecords')

if __name__ == '__main__':
  tf.app.run()
