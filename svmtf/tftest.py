# source activate tensorflow
# source deactivate
# /usr/noah/anaconda3/envs/tensorflow/lib/python3.4/site-packages/tensorflow

import tensorflow as tf
hello = tf.constant('Hello, TensorFlow!')
sess = tf.Session()
a = tf.constant(10)
b = tf.constant(32)
print(sess.run(a + b))
