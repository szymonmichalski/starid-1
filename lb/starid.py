import subprocess
import re
import time
import numpy as np
import tensorflow as tf
import model
import mnist_to_tfrecords

FLAGS = tf.app.flags.FLAGS
tf.app.flags.DEFINE_string('checkpoint_dir', '/home/noah/starid/lb/models', '')
resultscnt = 25
results = np.zeros(shape=(resultscnt, 6), dtype=float)

def identifyCentralStar(imgndx):
  tf.reset_default_graph()
  images = mnist_to_tfrecords.read_images('/home/noah/starid/stars/data/images_b1.mnist')
  image = images[imgndx,:,:,0]
  image = tf.cast(image, tf.float32) * (1. / 255) - 0.5
  image = tf.reshape(image, [28, 28, 1])
  softmax = model.inference(image)
  saver = tf.train.Saver()
  ckpt = tf.train.get_checkpoint_state(FLAGS.checkpoint_dir)
  sess = tf.Session()
  saver.restore(sess, ckpt.model_checkpoint_path)
  softmaxval = sess.run(softmax)
  ndx = np.argmax(softmaxval)
  return ndx

for resultsndx in range(0, resultscnt):
  starndx = np.mod(resultsndx, 10)
  starsetndx = np.random.randint(0, 1000)
  imgndx = starndx + starsetndx*10
  results[resultsndx, 0] = starndx
  results[resultsndx, 1] = imgndx

  t1 = time.time()
  starndx1 = identifyCentralStar(imgndx)
  if starndx1 == results[resultsndx, 0]:
    results[resultsndx, 2] = 1
  results[resultsndx, 3] = float(time.time() - t1)

  t2 = time.time()
  out = subprocess.check_output(['/home/noah/dev/starid/rb/rb', '--imgndx %d' % starndx])
  starndx2 = int(re.search(r'identification (\d+)', out.decode('utf-8')).group(1))
  if starndx2 == results[resultsndx, 0]:
    results[resultsndx, 4] = 1
  results[resultsndx, 5] = float(time.time() - t2)

  print('%5.0f, %5.0f, %1.0f, %1.0f' % (results[resultsndx, 0], results[resultsndx, 1], results[resultsndx, 2], results[resultsndx, 4]))

print()
print('%5s  %5s  %5s' % ('n %i' % resultscnt, 'ok', 't'))
print('%5s  %5s  %5s' % ('-----', '-----', '-----'))
print('%5s  %4.3f  %4.3f' % ('lb', np.mean(results[:,2]), np.mean(results[:,3])))
print('%5s  %4.3f  %4.3f' % ('rb', np.mean(results[:,4]), np.mean(results[:,5])))
