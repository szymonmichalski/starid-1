import tensorflow as tf

def variable_summaries(var, name):
  with tf.name_scope('summaries'):
    mean = tf.reduce_mean(var)
    tf.scalar_summary('mean/' + name, mean)
    with tf.name_scope('stddev'):
      stddev = tf.sqrt(tf.reduce_sum(tf.square(var - mean)))
    tf.scalar_summary('sttdev/' + name, stddev)
    tf.scalar_summary('max/' + name, tf.reduce_max(var))
    tf.scalar_summary('min/' + name, tf.reduce_min(var))
    tf.histogram_summary(name, var)

def weight_variable(shape):
  initial = tf.truncated_normal(shape, stddev=0.1)
  return tf.Variable(initial)

def bias_variable(shape):
  initial = tf.constant(0.1, shape=shape)
  return tf.Variable(initial)

def conv2d(x, W):
  return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='SAME')

def max_pool_2x2(x):
  return tf.nn.max_pool(x, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')

def inference(images):
  with tf.variable_scope('conv1') as scope:
    with tf.name_scope('weights'):
      W_conv1 = weight_variable([5, 5, 1, 32])
      variable_summaries(W_conv1, 'conv1/weights')
    with tf.name_scope('biases'):
      b_conv1 = bias_variable([32])
      variable_summaries(b_conv1, 'conv1/biases')
    x_image = tf.reshape(images, [-1, 28, 28, 1])
    h_conv1 = tf.nn.relu(conv2d(x_image, W_conv1) + b_conv1)
    h_pool1 = max_pool_2x2(h_conv1)

  with tf.variable_scope('conv2') as scope:
    with tf.name_scope('weights'):
      W_conv2 = weight_variable([5, 5, 32, 64])
      variable_summaries(W_conv2, 'conv2/weights')
    with tf.name_scope('biases'):
      b_conv2 = bias_variable([64])
      variable_summaries(b_conv2, 'conv2/biases')
    h_conv2 = tf.nn.relu(conv2d(h_pool1, W_conv2) + b_conv2)
    h_pool2 = max_pool_2x2(h_conv2)

  with tf.variable_scope('fullconn') as scope:
    W_fc1 = weight_variable([7 * 7 * 64, 1024])
    b_fc1 = bias_variable([1024])
    h_pool2_flat = tf.reshape(h_pool2, [-1, 7 * 7 * 64])
    h_fc1 = tf.nn.relu(tf.matmul(h_pool2_flat, W_fc1) + b_fc1)
    keep_prob = 1.0  # tf.placeholder(tf.float32)
    h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)

  with tf.variable_scope('readout'):
    W_fc2 = weight_variable([1024, 10])
    b_fc2 = bias_variable([10])
    logits = tf.nn.softmax(tf.matmul(h_fc1_drop, W_fc2) + b_fc2)
  return logits

def loss(logits, labels):
  labels = tf.to_int64(labels)
  cross_entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(logits, labels)
  with tf.name_scope('loss'):
     loss = tf.reduce_mean(cross_entropy)
      # loss = tf.reduce_mean( -tf.reduce_sum(labels * tf.log(logits), reduction_indices=[1]) )
     variable_summaries(loss, 'loss')
  return loss

def train(loss):
  with tf.name_scope('trainstep'):
    trainstep = tf.train.AdamOptimizer(1e-4).minimize(loss)
    #variable_summaries(trainstep, 'trainstep')
  return trainstep
