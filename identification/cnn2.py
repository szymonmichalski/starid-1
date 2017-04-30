### *cnn2* cnn using libstarid
###

import numpy as np
import tensorflow as tf

w1 = tf.Variable(tf.truncated_normal([5, 5, 1, 32], stddev=0.1), dtype=tf.float32)
b1 = tf.Variable(tf.constant(0.1, shape=[32]), dtype=tf.float32)
w2 = tf.Variable(tf.truncated_normal([5, 5, 32, 64], stddev=0.1), dtype=tf.float32)
b2 = tf.Variable(tf.constant(0.1, shape=[64]), dtype=tf.float32)
w3 = tf.Variable(tf.truncated_normal([7*7*64, 1024], stddev=0.1), dtype=tf.float32)
b3 = tf.Variable(tf.constant(0.1, shape=[1024]), dtype=tf.float32)
w4 = tf.Variable(tf.truncated_normal([1024, 10], stddev=0.1), dtype=tf.float32)
b4 = tf.Variable(tf.constant(0.1, shape=[10]), dtype=tf.float32)

def inference(x):
    conv1 = tf.nn.conv2d(x, w1, strides=[1, 1, 1, 1], padding='SAME') + b1
    acti1 = tf.nn.relu(conv1)
    pool1 = tf.nn.max_pool(acti1, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')
    conv2 = tf.nn.conv2d(pool1, w2, strides=[1, 1, 1, 1], padding='SAME') + b2
    acti2 = tf.nn.relu(conv2)
    pool2 = tf.nn.max_pool(acti2, ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')
    full3 = tf.matmul(tf.reshape(pool2, [-1, 7*7*64]), w3) + b3
    acti3 = tf.nn.relu(full3)
    drop3 = tf.nn.dropout(acti3, 1.0)
    full4 = tf.matmul(drop3, w4) + b4
    return tf.nn.softmax(full4)

def loss(ypred, y):
    cross_entropy = tf.nn.sparse_softmax_cross_entropy_with_logits(logits=ypred, labels=y)
    return tf.reduce_mean(cross_entropy)

def inputs():
    x = np.zeros((10, 28, 28, 1), dtype=np.float32)
    y = np.zeros((10), dtype=np.int32)
    return x, y

def train(lossval):
    return tf.train.AdamOptimizer(1e-4).minimize(lossval)

def evaluate(sess, x, y):
    return

saver = tf.train.Saver()
with tf.Session() as sess:
    tf.global_variables_initializer().run()
    x, y = inputs()
    ypred = inference(x)
    lossval = loss(ypred, y)
    trainop = train(lossval)
    coord = tf.train.Coordinator()
    threads = tf.train.start_queue_runners(sess=sess, coord=coord)

    training_steps = 1000
    for step in range(training_steps):
        # sess.run([trainop])
        if step % 100 == 0:
            print('loss ')
            # print('loss ', sess.run([lossval]))
        if step % 500 == 0:
            saver.save(sess, 'data_cnn2/model', global_step=step)

    evaluate(sess, x, y)
    saver.save(sess, 'data_cnn2/model', global_step=training_steps)
    coord.request_stop()
    coord.join(threads)
    sess.close()