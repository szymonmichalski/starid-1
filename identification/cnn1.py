### *cnn1* cnn using tfrecords
###

from tensorflow.python.platform import gfile
import numpy as np
import tensorflow as tf
import time

FLAGS = tf.app.flags.FLAGS
tf.app.flags.DEFINE_string('checkpoint_dir', '/home/noah/starid/identification/data_cnn1', '')
tf.app.flags.DEFINE_string('ckpt', '/home/noah/starid/identification/data_cnn1/model.ckpt', '')
tf.app.flags.DEFINE_string('examples', '/home/noah/starid/identification/data_cnn1/train', '')
tf.app.flags.DEFINE_string('num_examples', 60000, '')
tf.app.flags.DEFINE_integer('batch_size', 100, '')
tf.app.flags.DEFINE_integer('max_steps', 600, '')


def weight_variable(shape):
    initial = tf.truncated_normal(shape, stddev=0.1)
    return tf.Variable(initial)


def bias_variable(shape):
    initial = tf.constant(0.1, shape=shape)
    return tf.Variable(initial)


def conv2d(x, w):
    return tf.nn.conv2d(x, w, strides=[1, 1, 1, 1], padding='SAME')


def max_pool_2x2(x):
    return tf.nn.max_pool(x, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')


def inference(images):
    x_image = tf.reshape(images, [-1, 28, 28, 1])

    w_conv1 = weight_variable([5, 5, 1, 32])
    b_conv1 = bias_variable([32])
    h_conv1 = tf.nn.relu(conv2d(x_image, w_conv1) + b_conv1)
    h_pool1 = max_pool_2x2(h_conv1)

    w_conv2 = weight_variable([5, 5, 32, 64])
    b_conv2 = bias_variable([64])
    h_conv2 = tf.nn.relu(conv2d(h_pool1, w_conv2) + b_conv2)
    h_pool2 = max_pool_2x2(h_conv2)

    w_fc1 = weight_variable([7 * 7 * 64, 1024])
    b_fc1 = bias_variable([1024])
    h_pool2_flat = tf.reshape(h_pool2, [-1, 7 * 7 * 64])
    h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, w_fc1) + b_fc1)
    h_fc1_drop = tf.nn.dropout(h_fc1, 1.0)

    w_fc2 = weight_variable([1024, 10])
    b_fc2 = bias_variable([10])
    softmax = tf.nn.softmax(tf.matmul(h_fc1_drop, w_fc2) + b_fc2)
    return softmax


def get_example(filename_queue):
    reader = tf.TFRecordReader()
    _, record = reader.read(filename_queue)
    features = tf.parse_single_example(record, features={
        'height': tf.FixedLenFeature([], tf.int64),
        'width': tf.FixedLenFeature([], tf.int64),
        'depth': tf.FixedLenFeature([], tf.int64),
        'label': tf.FixedLenFeature([], tf.int64),
        'image_raw': tf.FixedLenFeature([], tf.string),
    })
    image = tf.decode_raw(features['image_raw'], tf.uint8)
    image.set_shape([28 * 28])
    image = tf.cast(image, tf.float32) * (1. / 255) - 0.5

    class Example(object):
        pass

    example = Example()
    example.height = tf.cast(features['height'], tf.int32)
    example.width = tf.cast(features['width'], tf.int32)
    example.depth = tf.cast(features['depth'], tf.int32)
    example.label = tf.cast(features['label'], tf.int32)
    example.image = tf.reshape(image, [28, 28, 1])
    return example


def get_batch(example, min_queue_examples, FLAGS, shuffle):
    num_preprocess_threads = 2
    if shuffle:
        images, labels = tf.train.shuffle_batch(
            [example.image, example.label],
            batch_size=FLAGS.batch_size,
            num_threads=num_preprocess_threads,
            capacity=min_queue_examples + 3 * FLAGS.batch_size,
            min_after_dequeue=min_queue_examples)
    else:
        images, labels = tf.train.batch(  # def cost(softmax, labels):
            [example.image, example.label],
            batch_size=FLAGS.batch_size,
            num_threads=num_preprocess_threads,
            capacity=min_queue_examples + 3 * FLAGS.batch_size)
    tf.summary.image('images', images)
    return images, tf.reshape(labels, [FLAGS.batch_size])


def inputs(FLAGS):
    min_queue_examples = int(0.4 * FLAGS.num_examples)
    filenames = [FLAGS.examples]
    filename_queue = tf.train.string_input_producer(filenames)
    example = get_example(filename_queue)
    images, labels = get_batch(example, min_queue_examples, FLAGS, shuffle=False)
    return images, labels


def _int64_feature(value):
    return tf.train.Feature(int64_list=tf.train.Int64List(value=[value]))


def _bytes_feature(value):
    return tf.train.Feature(bytes_list=tf.train.BytesList(value=[value]))


def _read32(bytestream):
    dt = np.dtype(np.uint32).newbyteorder('>')
    return np.frombuffer(bytestream.read(4), dtype=dt)[0]


def read_images(filename):
    with gfile.Open(filename, 'identification') as bytestream:
        magic = _read32(bytestream)
        if magic != 2051:
            raise ValueError('magic number error %s' % (magic, filename))
        num_images = _read32(bytestream)
        rows = _read32(bytestream)
        cols = _read32(bytestream)
        buf = bytestream.read()  # read(rows * cols * num_images)
        data = np.frombuffer(buf, dtype=np.uint8)
        data = data.reshape(num_images, rows, cols, 1)
        return data


def read_labels(filename, one_hot=False, num_classes=10):
    with gfile.Open(filename, 'identification') as bytestream:
        magic = _read32(bytestream)
        if magic != 2049:
            raise ValueError('magic number error %s' % (magic, filename))
        num_items = _read32(bytestream)
        buf = bytestream.read()  # read(num_items)
        labels = np.frombuffer(buf, dtype=np.uint8)
        if one_hot:
            return dense_to_one_hot(labels, num_classes)
        return labels


def dense_to_one_hot(labels_dense, num_classes):
    num_labels = labels_dense.shape[0]
    index_offset = np.arange(num_labels) * num_classes
    labels_one_hot = np.zeros((num_labels, num_classes))
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
        example = tf.train.Example(
            features=tf.train.Features(feature={
                'height': _int64_feature(rows),
                'width': _int64_feature(cols),
                'depth': _int64_feature(depth),
                'label': _int64_feature(int(labels[index])),
                'image_raw': _bytes_feature(image_raw)
            })
        )
        record = example.SerializeToString()
        writer.write(record)
    writer.close()


def train():
    images, labels = inputs(FLAGS)
    softmax = inference(images)
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


def eval():
    tf.app.flags.DEFINE_string('examples', '/home/noah/starid/identification/data_cnn1/eval', '')
    tf.app.flags.DEFINE_string('num_examples', 10000, '')
    tf.app.flags.DEFINE_string('batch_size', 100, '')
    tf.app.flags.DEFINE_integer('max_steps', 100, '')
    images, labels = inputs(FLAGS)
    softmax = inference(images)
    prediction = tf.nn.in_top_k(softmax, labels, 1)
    saver = tf.train.Saver()
    ckpt = tf.train.get_checkpoint_state(FLAGS.checkpoint_dir)
    sess = tf.Session()
    saver.restore(sess, ckpt.model_checkpoint_path)
    coord = tf.train.Coordinator()
    threads = []
    for qr in tf.get_collection(tf.GraphKeys.QUEUE_RUNNERS):
        threads.extend(qr.create_threads(sess, coord=coord, daemon=True, start=True))
    goodcnt = 0
    for step in range(FLAGS.max_steps):
        predictions = sess.run([prediction])
        goodcnt += np.sum(predictions)
    precision = goodcnt / FLAGS.num_examples
    print('%.3f correct' % precision)
    coord.request_stop()
    coord.join(threads, stop_grace_period_secs=10)


def main(argv):
    train()
    return


if __name__ == '__main__':
    tf.app.run()
