### *rnn2* rnn using libstarid
###

import random
import numpy as np
import tensorflow as tf
import libstarid.libstarid as ls
libstarid = ls.libstarid()

data = tf.placeholder(tf.float32, [None, 36,1])
target = tf.placeholder(tf.float32, [None, 10])

def inputs(batch_size):
    angseqs = np.zeros((batch_size, 36, 1), dtype=np.float32)
    starndxs = np.zeros((batch_size, 10), dtype=np.int32)
    for batchndx in range(batch_size):
        starndx = random.randint(0, 9)
        angseqs[batchndx, :, :] = libstarid.ang_seq_vec(starndx=starndx)
        starndxs[batchndx, starndx] = 1
    return angseqs, starndxs

num_hidden = 24
cell = tf.contrib.rnn.BasicLSTMCell(num_hidden,state_is_tuple=True)
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
accuracy = 1 - tf.reduce_mean(tf.cast(mistakes, tf.float32))

saver = tf.train.Saver()
init = tf.initialize_all_variables()
sess = tf.Session()
sess.run(init)
for batchndx in range(500):
    angseqs, starndxs = inputs(batch_size=100)
    sess.run(minimize, {data: angseqs, target: starndxs})
    if batchndx % 10 == 0:
        print('batchndx %d loss %3.2f accuracy %3.2f'
              % (batchndx, sess.run(cross_entropy, feed_dict={data: angseqs, target: starndxs}),
                 sess.run(accuracy, feed_dict={data: angseqs, target: starndxs})))
saver.save(sess, 'data_rnn2/model', global_step=batchndx)
sess.close()