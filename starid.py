### *starid*
###
### demonstration, testing, and evaluation
###
import subprocess
import re
import numpy as np
import tensorflow as tf
import matplotlib.pyplot as plt
import lb.amodel
import lb.acontainer_make

### *lb* uses a convolutional network with training and evaluation input files based on the classic mnist format.
###
def lb(starndx):
    FLAGS = tf.app.flags.FLAGS
    tf.app.flags.DEFINE_string('checkpoint_dir', '/home/noah/starid/lb/adata', '')
    imgndx = starndx + 10 * np.random.randint(0, 1000)
    tf.reset_default_graph()
    images = lb.acontainer_make.read_images('/home/noah/starid/stars/data/eval_examples')
    image = images[imgndx, :, :, 0]
    image = tf.cast(image, tf.float32) * (1. / 255) - 0.5
    image = tf.reshape(image, [28, 28, 1])
    softmax = lb.amodel.inference(image)
    saver = tf.train.Saver()
    ckpt = tf.train.get_checkpoint_state(FLAGS.checkpoint_dir)
    sess = tf.Session()
    saver.restore(sess, ckpt.model_checkpoint_path)
    softmaxval = sess.run(softmax)
    result = np.argmax(softmaxval)
    return result

### *rb* uses triangular structure in the star image.
###
def rb(starndx):
    output = subprocess.check_output(['/home/noah/starid/rb/rb', '--starndx', str(starndx)])
    result = int(re.search(r'identification = (\d+)', output.decode('utf-8')).group(1))
    return result

### *libstarsop* generates and plots a star image numpy array.
###
def imgop(starndx):
    libimgop = tf.load_op_library('libstarsop/libstarsop.so')
    with tf.Session(''):
        image = libimgop.image(np.zeros(shape=(28, 28))).eval()
    plt.matshow(-1 * image, cmap='Greys', interpolation='nearest')
    plt.show()
    return image

### *main*
###
starndx = 1
image = imgop(starndx)
reslb = lb(starndx)
resrb = rb(starndx)


