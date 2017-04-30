import numpy as np
import tensorflow as tf
import identification.cnn1

def cnn1(image):
    FLAGS = tf.app.flags.FLAGS
    tf.reset_default_graph()
    image = tf.cast(image, tf.float32) - 0.5
    image = tf.reshape(image, [28, 28, 1])
    softmax = identification.cnn1.inference(image)
    saver = tf.train.Saver()
    ckpt = tf.train.get_checkpoint_state(FLAGS.checkpoint_dir)
    sess = tf.Session()
    saver.restore(sess, ckpt.model_checkpoint_path)
    softmaxval = sess.run(softmax)
    result = np.argmax(softmaxval)
    return result