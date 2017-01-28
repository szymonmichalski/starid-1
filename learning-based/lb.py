from optparse import OptionParser
from data import mnist_to_tfrecords
import tensorflow as tf
import graph as gn
import numpy as np
FLAGS = tf.app.flags.FLAGS
tf.app.flags.DEFINE_string('checkpoint_dir', '/home/noah/dev/starid/models', '')

### **identify central star**
###
### predicts the starndx of the star at the center of the image
###
def identifyCentralStar(imgndx):
  tf.reset_default_graph()
  images = mnist_to_tfrecords.read_images('/home/noah/dev/starid/data/images_b1.mnist')
  image = images[imgndx,:,:,0]
  image = tf.cast(image, tf.float32) * (1. / 255) - 0.5
  image = tf.reshape(image, [28, 28, 1])
  softmax = gn.inference(image)
  saver = tf.train.Saver()
  ckpt = tf.train.get_checkpoint_state(FLAGS.checkpoint_dir)
  sess = tf.Session()
  saver.restore(sess, ckpt.model_checkpoint_path)
  softmaxval = sess.run(softmax)
  ndx = np.argmax(softmaxval)
  return ndx

def main():
  usage = "usage: %lb [options] arg"
  parser = OptionParser(usage)
  parser.add_option('-s', '--starndx', dest='starndx', help='')
  (options, args) = parser.parse_args()

if __name__ == "__main__":
  main()