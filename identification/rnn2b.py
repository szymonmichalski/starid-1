### recursive network using libstarid cpp eigen kernel and tensorflow training and inference
###
import random
import numpy as np
import tensorflow as tf
import libstarid.libstarid as ls
import time
libstarid = ls.libstarid()
stars = 1000
batch = 1000
batches = 1
lstmsize = 100
rnnlayers = 1
dropout = 0.5
beta = 0.01
loginterval = 100 # batches
outdir = '/home/noah/run' + time.strftime('%m%d%H%M%S')

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
rnn1 = tf.contrib.rnn.BasicLSTMCell(lstmsize, state_is_tuple=True)
rnn1 = tf.contrib.rnn.DropoutWrapper(rnn1, output_keep_prob=dropout)
rnn1 = tf.contrib.rnn.MultiRNNCell([rnn1] * rnnlayers, state_is_tuple=True)
out, state = tf.nn.dynamic_rnn(rnn1, data, dtype=tf.float32)
out = tf.transpose(out, [1, 0, 2])
outf = tf.gather(out, int(out.get_shape()[0]-1))
w1 = tf.Variable(tf.truncated_normal([lstmsize, stars]))
b1 = tf.Variable(tf.constant(0.1, shape=[stars]))
r1 = tf.nn.l2_loss(w1) * beta
logits = tf.matmul(outf, w1) + b1

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
    trainin, trainlab = inputs(batch, stars)
    sess.run(train, {data: trainin, target: trainlab})
    if batchndx % loginterval == 0:
        testin, testlab = inputs(batch, stars)
        testcost, testacc, teststats = sess.run([loss, accuracy, stats], {data: testin, target: testlab})
        writer.add_summary(teststats, batchndx)
        print('%s, %.1f, %d, %.4f, %.4f' % (time.strftime('%H%M%S'), time.time()-t0, batchndx, testcost, testacc))
saver = tf.train.Saver()
saver.save(sess, outdir+'/model', global_step=batchndx)
sess.close()