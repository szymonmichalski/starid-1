### *starid*
###
### demonstration, testing, and evaluation
###
import subprocess
import re
import time
import numpy as np
import tensorflow as tf
import lb.amodel
import lb.acontainer_make

FLAGS = tf.app.flags.FLAGS
tf.app.flags.DEFINE_string('checkpoint_dir', '/home/noah/starid/lb/adata', '')
resultscnt = 5
results = np.zeros(shape=(resultscnt, 3), dtype=float)

### *lb a* uses a convolutional network with training and evaluation input files based on the classic mnist format. systems that process classic mnist are compatible.
###
def lb_a(imgndx):
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

### *rb a* uses triangular structure in the star image.
###
def rb_a(starndx):
    output = subprocess.check_output(['/home/noah/starid/rb/rb', '--starndx', str(starndx)])
    result = int(re.search(r'identification = (\d+)', output.decode('utf-8')).group(1))
    return result

### *main*
###
for resultsndx in range(0, resultscnt):
    starndx = np.mod(resultsndx, 10)
    results[resultsndx, 0] = starndx
    results[resultsndx, 1] = lb_a(starndx)
    results[resultsndx, 2] = rb_a(starndx)
