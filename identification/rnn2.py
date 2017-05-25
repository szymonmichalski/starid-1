### python numpy, cpp eigen kernel, tensorflow training and inference
###
import time
import random
import numpy as np
import tensorflow as tf
import libstarid.libstarid as ls
libstarid = ls.libstarid()
stars = 100
sequence_length = 36
batch_size = 100
batches = 100
num_units = 64

def inputs(batch, stars):
    angseqs = np.zeros((batch, sequence_length, 1), dtype=np.float32)
    labels = np.zeros((batch), dtype=np.int32)
    for batchndx in range(batch):
        starndx = random.randint(0, stars-1)
        angseqs[batchndx, :, :] = libstarid.ang_seq_vec(starndx)
        labels[batchndx] = starndx
    return angseqs, labels

data = tf.placeholder(tf.float32, [batch_size, sequence_length, 1])
target = tf.placeholder(tf.int32, [batch_size])
w1 = tf.Variable(tf.truncated_normal([num_units, stars]))
b1 = tf.Variable(tf.constant(0.1, shape=[stars]))

cell = tf.contrib.rnn.BasicLSTMCell(num_units, state_is_tuple=True)
init_state = cell.zero_state(batch_size, tf.float32)
rnn_outputs, final_state = tf.nn.dynamic_rnn(cell, data, initial_state=init_state)
rnn_outputs = tf.gather(tf.transpose(rnn_outputs, [1, 0, 2]), sequence_length-1)
logits = tf.matmul(rnn_outputs, w1) + b1

loss = tf.reduce_mean(tf.nn.sparse_softmax_cross_entropy_with_logits(logits=logits, labels=target))
train = tf.train.AdamOptimizer().minimize(loss)
prediction = tf.cast(tf.arg_max((logits), 1), tf.int32)
accuracy = tf.reduce_mean(tf.cast(tf.equal(prediction, target), tf.float32))

init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)
t0 = time.time()
for batchndx in range(batches):
    trainin, trainlab = inputs(batch_size, stars)
    sess.run(train, {data: trainin, target: trainlab})
    if batchndx % 10 == 0:
        testin, testlab = inputs(batch_size, stars)
        testcost, testacc = sess.run([loss, accuracy], {data: testin, target: testlab})
        print('%s, %.1f, %d, %.4f, %.4f' % (time.strftime('%H%M%S'), time.time()-t0, batchndx, testcost, testacc))
