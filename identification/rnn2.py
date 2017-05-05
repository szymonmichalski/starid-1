### *rnn2* rnn using libstarid
###

import random
import numpy as np
import tensorflow as tf
import libstarid.libstarid as ls
libstarid = ls.libstarid()

data = tf.placeholder(tf.float32, [None, 36,1])
target = tf.placeholder(tf.float32, [None, 1])

def inputs(batch_size):
    angseqs = np.zeros((batch_size, 36, 1), dtype=np.float32)
    starndxs = np.zeros((batch_size), dtype=np.int32)
    for cnt in range(batch_size):
        starndx = random.randint(0, 9)
        angseqs[cnt, :, :] = libstarid.ang_seq_vec(starndx=starndx)
        starndxs[cnt] = starndx
    return angseqs, starndxs

num_hidden = 24
cell = tf.nn.rnn_cell.LSTMCell(num_hidden,state_is_tuple=True)
val, _ = tf.nn.dynamic_rnn(cell, data, dtype=tf.float32)
val = tf.transpose(val, [1, 0, 2])
last = tf.gather(val, int(val.get_shape()[0]) - 1)
weight = tf.Variable(tf.truncated_normal([num_hidden, int(target.get_shape()[1])]))
bias = tf.Variable(tf.constant(0.1, shape=[target.get_shape()[1]]))
prediction = tf.nn.softmax(tf.matmul(last, weight) + bias)

cross_entropy = -tf.reduce_sum(target * tf.log(tf.clip_by_value(prediction, 1e-10, 1.0)))
optimizer = tf.train.AdamOptimizer()
minimize = optimizer.minimize(cross_entropy)
mistakes = tf.not_equal(tf.argmax(target, 1), tf.argmax(prediction, 1))
error = tf.reduce_mean(tf.cast(mistakes, tf.float32))
init_op = tf.initialize_all_variables()
sess = tf.Session()
sess.run(init_op)
for batchndx in range(200):
    angseqs, starndxs = inputs(batch_size=100)
    sess.run(minimize, {data: angseqs, target: starndxs})
    print('batchndx %d' % (batchndx))
sess.close()