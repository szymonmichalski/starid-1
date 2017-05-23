### machine learning using cpp eigen kernel and tensorflow training and inference
###
import time
import random
import numpy as np
import tensorflow as tf
import libstarid.libstarid as ls
libstarid = ls.libstarid()
stars = 100
batch = 100
batches = 300
lstmsize = 100

def inputs(batch, stars):
    angseqs = np.zeros((batch, 36, 1), dtype=np.float32)
    labels = np.zeros((batch), dtype=np.int32)
    for batchndx in range(batch):
        starndx = random.randint(0, stars-1)
        angseqs[batchndx, :, :] = libstarid.ang_seq_vec(starndx)
        labels[batchndx] = starndx
    return angseqs, labels

data = tf.placeholder(tf.float32, [batch, 36,1])
target = tf.placeholder(tf.int32, [batch])
w1 = tf.Variable(tf.truncated_normal([lstmsize, stars]))
b1 = tf.Variable(tf.constant(0.1, shape=[stars]))
lstm = tf.contrib.rnn.BasicLSTMCell(lstmsize, state_is_tuple=True)
outj, state = tf.nn.dynamic_rnn(lstm, data, dtype=tf.float32)
outj = tf.transpose(outj, [1, 0, 2])
outf = tf.gather(outj, int(outj.get_shape()[0]-1))
logits = tf.matmul(outf, w1) + b1

loss = tf.reduce_mean(tf.nn.sparse_softmax_cross_entropy_with_logits(logits=logits, labels=target))
train = tf.train.AdamOptimizer().minimize(loss)
prediction = tf.cast(tf.arg_max((logits), 1), tf.int32)
accuracy = tf.reduce_mean(tf.cast(tf.equal(prediction, target), tf.float32))

init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)
t0 = time.time()
for batchndx in range(batches):
    trainin, trainlab = inputs(batch, stars)
    sess.run(train, {data: trainin, target: trainlab})
    if batchndx % 10 == 0:
        testin, testlab = inputs(batch, stars)
        testcost, testacc = sess.run([loss, accuracy], {data: testin, target: testlab})
        print('%s, %.1f, %d, %.4f, %.4f' % (time.strftime('%H%M%S'), time.time()-t0, batchndx, testcost, testacc))
