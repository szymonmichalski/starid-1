### recursive network using libstarid cpp eigen kernel and tensorflow training and inference
###
import random
import numpy as np
import tensorflow as tf
import libstarid.libstarid as ls
import time
libstarid = ls.libstarid()
stars = 1000
sequence_length = 36
batch_size = 1000
batches = 10
state_size = 64
rnnlayers = 1
output_keep_prob = 0.5
beta = 0.01
loginterval = 10 # batches
outdir = '/home/noah/run' + time.strftime('%m%d%H%M%S')

def inputs(batch, stars):
    sequences = np.zeros((batch, sequence_length, 1), dtype=np.float32)
    labels = np.zeros((batch), dtype=np.int32)
    for batchndx in range(batch):
        starndx = random.randint(0, stars-1)
        sequence = libstarid.ang_seq_vec(starndx)
        sequences[batchndx, :, :] = sequence
        labels[batchndx] = starndx
        hist, bin_edges = np.histogram(sequence, bins=[0, 1, 2, 3, 4, 5, 6])
        print(hist)
    print("max sequence value %d" % np.max(sequences)) # max value is 6 for stars = 1000
    return sequences, labels

data = tf.placeholder(tf.float32, [batch_size, sequence_length, 1])
target = tf.placeholder(tf.int32, [batch_size])
w1 = tf.Variable(tf.truncated_normal([state_size, stars]))
b1 = tf.Variable(tf.constant(0.1, shape=[stars]))
r1 = tf.nn.l2_loss(w1) * beta

cell = tf.contrib.rnn.GRUCell(state_size)
cell = tf.contrib.rnn.DropoutWrapper(cell, output_keep_prob=output_keep_prob)
cell = tf.contrib.rnn.MultiRNNCell([cell] * rnnlayers, state_is_tuple=True)
init_state = cell.zero_state(batch_size, tf.float32)
rnn_outputs, final_state = tf.nn.dynamic_rnn(cell, data, initial_state=init_state)
rnn_outputs = tf.gather(tf.transpose(rnn_outputs, [1, 0, 2]), sequence_length-1)
logits = tf.matmul(rnn_outputs, w1) + b1

loss = tf.reduce_mean(tf.nn.sparse_softmax_cross_entropy_with_logits(logits=logits, labels=target))
loss = tf.reduce_mean(loss + r1)
train = tf.train.AdamOptimizer().minimize(loss)
prediction = tf.cast(tf.arg_max((logits), 1), tf.int32)
accuracy = tf.reduce_mean(tf.cast(tf.equal(prediction, target), tf.float32))

tf.summary.histogram('w1', w1)
tf.summary.histogram('b1', b1)
tf.summary.histogram('r1', r1)
tf.summary.histogram('logits', logits)
tf.summary.scalar('loss', loss)
tf.summary.scalar('accuracy', accuracy)
stats = tf.summary.merge_all()
saver = tf.train.Saver()
writer = tf.summary.FileWriter(outdir)

init = tf.global_variables_initializer()
sess = tf.Session()
sess.run(init)
writer.add_graph(sess.graph)
t0 = time.time()
for batchndx in range(batches):
    trainin, trainlab = inputs(batch_size, stars)
    sess.run(train, {data: trainin, target: trainlab})
    if batchndx % loginterval == 0:
        testin, testlab = inputs(batch_size, stars)
        testcost, testacc, teststats = sess.run([loss, accuracy, stats], {data: testin, target: testlab})
        writer.add_summary(teststats, batchndx)
        print('%s, %.1f, %d, %.4f, %.4f' % (time.strftime('%H%M%S'), time.time()-t0, batchndx, testcost, testacc))
saver = tf.train.Saver()
saver.save(sess, outdir+'/model', global_step=batchndx)
sess.close()