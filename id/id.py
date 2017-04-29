import numpy as np
import tensorflow as tf
import id.tf1

def lb(image):
    FLAGS = tf.app.flags.FLAGS
    tf.app.flags.DEFINE_string('checkpoint_dir', '/home/noah/starid/id/tf1_data', '')
    tf.reset_default_graph()
    # imgndx = starndx + 10 * np.random.randint(0, 1000)
    # images = lb.acontainer_make.read_images('/home/noah/starid/stars/data/eval_examples')
    # image = images[imgndx, :, :, 0]
    image = tf.cast(image, tf.float32) * (1. / 255) - 0.5
    image = tf.reshape(image, [28, 28, 1])
    softmax = id.tf1.inference(image)
    saver = tf.train.Saver()
    ckpt = tf.train.get_checkpoint_state(FLAGS.checkpoint_dir)
    sess = tf.Session()
    saver.restore(sess, ckpt.model_checkpoint_path)
    softmaxval = sess.run(softmax)
    result = np.argmax(softmaxval)
    return result