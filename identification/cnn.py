### *convolutional network* cnn using libstarid, and tensorflow training and inference
###
import tensorflow as tf
import numpy as np
import time, random
import libstarid.libstarid as ls
libstarid = ls.libstarid()

stars = 1000
batch_size = 100
batches = 100
output_keep_prob = 0.5
beta = 0.01
loginterval = 10 # batches
outdir = '/home/noah/runs/' + time.strftime('%m%d%H%M%S')
keep_prob = tf.placeholder(tf.float32)

def inputs(batch_size, stars):
    images = np.zeros((batch_size, 28, 28, 1), dtype=np.float32)
    labels = np.zeros((batch_size), dtype=np.int32)
    for cnt in range(batch_size):
        starndx = random.randint(0, stars-1)
        images[cnt, :, :, 0] = libstarid.image(starndx)
        labels[cnt] = starndx
    return images, labels

def train():
    data = tf.placeholder(tf.float32, [batch_size, 28, 28, 1])
    target = tf.placeholder(tf.int32, [batch_size])
    w1 = tf.Variable(tf.truncated_normal([5, 5, 1, 32], stddev=0.1), dtype=tf.float32)
    b1 = tf.Variable(tf.constant(0.1, shape=[32]), dtype=tf.float32)
    r1 = tf.nn.l2_loss(w1) * beta
    w2 = tf.Variable(tf.truncated_normal([5, 5, 32, 64], stddev=0.1), dtype=tf.float32)
    b2 = tf.Variable(tf.constant(0.1, shape=[64]), dtype=tf.float32)
    r2 = tf.nn.l2_loss(w2) * beta
    w3 = tf.Variable(tf.truncated_normal([7 * 7 * 64, 1024], stddev=0.1), dtype=tf.float32)
    b3 = tf.Variable(tf.constant(0.1, shape=[1024]), dtype=tf.float32)
    r3 = tf.nn.l2_loss(w3) * beta
    w4 = tf.Variable(tf.truncated_normal([1024, stars], stddev=0.1), dtype=tf.float32)
    b4 = tf.Variable(tf.constant(0.1, shape=[stars]), dtype=tf.float32)
    r4 = tf.nn.l2_loss(w4) * beta

    conv1 = tf.nn.conv2d(data, w1, strides=[1, 1, 1, 1], padding='SAME') + b1
    pool1 = tf.nn.max_pool(tf.nn.relu(conv1), ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')
    conv2 = tf.nn.conv2d(pool1, w2, strides=[1, 1, 1, 1], padding='SAME') + b2
    pool2 = tf.nn.max_pool(tf.nn.relu(conv2), ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')
    full3 = tf.matmul(tf.reshape(pool2, [-1, 7 * 7 * 64]), w3) + b3
    drop3 = tf.nn.dropout(tf.nn.relu(full3), keep_prob)
    logits = tf.matmul(drop3, w4) + b4

    loss = tf.reduce_mean(tf.nn.sparse_softmax_cross_entropy_with_logits(logits=logits, labels=target))
    loss = tf.reduce_mean(loss + r1 + r2 + r3 + r4)
    train = tf.train.AdamOptimizer().minimize(loss)
    prediction = tf.cast(tf.arg_max((logits), 1), tf.int32)
    accuracy = tf.reduce_mean(tf.cast(tf.equal(prediction, target), tf.float32))

    tf.summary.histogram('w4', w4)
    tf.summary.histogram('b4', b4)
    tf.summary.histogram('r4', r4)
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
        sess.run(train, {data: trainin, target: trainlab, keep_prob: output_keep_prob})
        if batchndx % loginterval == 0:
            testin, testlab = inputs(batch_size, stars)
            testcost, testacc, teststats = sess.run([loss, accuracy, stats], {data: testin, target: testlab, keep_prob: 1.0})
            writer.add_summary(teststats, batchndx)
            print('%s, %.1f, %d, %.2f, %.2f' % (time.strftime('%H%M%S'), time.time()-t0, batchndx, testcost, testacc))
    saver = tf.train.Saver()
    saver.save(sess, outdir+'/model', global_step=batchndx)
    sess.close()

def train_minimalist():
    batch = 100
    data = tf.placeholder(tf.float32, [batch, 28, 28, 1])
    target = tf.placeholder(tf.int32, [batch])
    w1 = tf.Variable(tf.truncated_normal([5, 5, 1, 32], stddev=0.1), dtype=tf.float32)
    b1 = tf.Variable(tf.constant(0.1, shape=[32]), dtype=tf.float32)
    w2 = tf.Variable(tf.truncated_normal([5, 5, 32, 64], stddev=0.1), dtype=tf.float32)
    b2 = tf.Variable(tf.constant(0.1, shape=[64]), dtype=tf.float32)
    w3 = tf.Variable(tf.truncated_normal([7 * 7 * 64, 1024], stddev=0.1), dtype=tf.float32)
    b3 = tf.Variable(tf.constant(0.1, shape=[1024]), dtype=tf.float32)
    w4 = tf.Variable(tf.truncated_normal([1024, stars], stddev=0.1), dtype=tf.float32)
    b4 = tf.Variable(tf.constant(0.1, shape=[stars]), dtype=tf.float32)

    conv1 = tf.nn.conv2d(data, w1, strides=[1, 1, 1, 1], padding='SAME') + b1
    pool1 = tf.nn.max_pool(tf.nn.relu(conv1), ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')
    conv2 = tf.nn.conv2d(pool1, w2, strides=[1, 1, 1, 1], padding='SAME') + b2
    pool2 = tf.nn.max_pool(tf.nn.relu(conv2), ksize=[1, 2, 2, 1], strides=[1, 2, 2, 1], padding='SAME')
    full3 = tf.matmul(tf.reshape(pool2, [-1, 7 * 7 * 64]), w3) + b3
    logits = tf.matmul(full3, w4) + b4

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
            print('%s, %.1f, %d, %.2f, %.2f' % (time.strftime('%H%M%S'), time.time() - t0, batchndx, testcost, testacc))

if __name__ == '__main__':
    # train_minimalist()
    train()
