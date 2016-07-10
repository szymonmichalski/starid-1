import numpy as np
import tensorflow as tf
import convnet
import convnet_input

def train():
  input = convnet_input.read_data_sets('/tmp/data', one_hot=True)
  images = tf.placeholder(tf.float32, shape=[None, 784])
  labels = tf.placeholder(tf.float32, shape=[None, 10])

  logits = convnet.inference(images)
  loss = convnet.loss(logits, labels)
  train = convnet.train(loss)

  init = tf.initialize_all_variables()
  sess = tf.Session()
  sess.run(init)
  for i in range(10):
    batch = input.train.next_batch(50)
    loss_val = sess.run(loss, feed_dict={images: batch[0], labels: batch[1]})
    print("step %d, loss %g" % (i, loss_val))
    sess.run(train, feed_dict={images: batch[0], labels: batch[1]})

def main(argv=None):
  train()

if __name__ == '__main__':
  tf.app.run()
