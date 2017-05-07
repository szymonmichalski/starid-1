### *rnn2* rnn using libstarid
###

import random
import numpy as np
import tensorflow as tf
import libstarid.libstarid as ls
libstarid = ls.libstarid()
stars = 100
batch = 100
batches = 500
hidden = 24

def inputs(batch, stars):
    angseqs = np.zeros((batch, 36, 1), dtype=np.float32)
    labels = np.zeros((batch, stars), dtype=np.int32)
    for batchndx in range(batch):
        starndx = random.randint(0, stars-1)
        angseqs[batchndx, :, :] = libstarid.ang_seq_vec(starndx)
        labels[batchndx, starndx] = 1
    return angseqs, labels

data = tf.placeholder(tf.float32, [batch, 36,1])
target = tf.placeholder(tf.float32, [batch, stars])
cell = tf.contrib.rnn.BasicLSTMCell(hidden, state_is_tuple=True)
out, state = tf.nn.dynamic_rnn(cell, data, dtype=tf.float32)
out = tf.transpose(out, [1, 0, 2])
outf = tf.gather(out, int(out.get_shape()[0]-1))
weight = tf.Variable(tf.truncated_normal([hidden, stars]))
bias = tf.Variable(tf.constant(0.1, shape=[stars]))
softmax = tf.nn.softmax(tf.matmul(outf, weight) + bias)
cross_entropy = -tf.reduce_sum(target * tf.log(tf.clip_by_value(softmax, 1e-10, 1.0)))
minimize = tf.train.AdamOptimizer().minimize(cross_entropy)
errvec = tf.not_equal(tf.argmax(target, 1), tf.argmax(softmax, 1))
accuracy = 1 - tf.reduce_mean(tf.cast(errvec, tf.float32))

saver = tf.train.Saver()
init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)
for batchndx in range(batches):
    images, labels = inputs(batch, stars)
    sess.run(minimize, {data: images, target: labels})
    if batchndx % 10 == 0:
        images, labels = inputs(batch, stars)
        print('%5d %5.2f %5.2f' % (batchndx, sess.run(cross_entropy, {data: images, target: labels}), sess.run(accuracy, {data: images, target: labels})))
# saver.save(sess, 'data_rnn2/model', global_step=batchndx)
sess.close()