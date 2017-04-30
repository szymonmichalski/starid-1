### *cnn2* cnn using libstarid
###

import numpy as np
import tensorflow as tf

w = tf.Variable(tf.zeros([2, 1]))
b = tf.Variable(0.)

def inference(x):
    ypred = tf.matmul(x, w) + b
    return ypred

def loss(x, y):
    lossval = 0
    return lossval

def inputs():
    x = np.array([0, 0])
    y = 0
    return x, y

def train(lossval):
    return

def evaluate(sess, x, y):
    return

saver = tf.train.Saver()
with tf.Session() as sess:
    tf.global_variables_initializer().run()
    x, y = inputs()
    lossval = loss(x, y)
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