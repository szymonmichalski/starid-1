from optparse import OptionParser
from data import mnist
import tensorflow as tf
import graph as gn
import numpy as np

def identifyCentralStar(starndx=0):
  imgndx = int(starndx / 800) - 1
  FLAGS = tf.app.flags.FLAGS
  tf.app.flags.DEFINE_string('checkpoint_dir', '/home/noah/dev/starid/models', '')
  images = mnist.read_images('/home/noah/dev/starid/data/images_b1.mnist')
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
  return 800*(ndx+1)

def main():
  usage = "usage: %prog [options] arg"
  parser = OptionParser(usage)
  parser.add_option('-s', '--starndx', dest='starndx', help='')
  (options, args) = parser.parse_args()

if __name__ == "__main__":
  main()