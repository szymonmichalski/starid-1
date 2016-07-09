
import numpy as np
import tensorflow as tf
import convnet
import convnet_input

def train():

    images, labels = convnet_input.training_inputs()
    logits = convnet.inference(images)
    loss = convnet.loss(logits, labels)
    train_op = convnet.train(loss)

    init = tf.initialize_all_variables()
    sess = tf.Session()
    sess.run(init)
    for i in range(10):
        loss_value = sess.run(loss)
        print("step %d, loss %g" % (i, loss_value))
        sess.run(train_op)

def main(argv=None):
    train()

if __name__ == '__main__':
    tf.app.run()
                            