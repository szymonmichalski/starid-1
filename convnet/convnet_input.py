
import tensorflow as tf
from tensorflow.examples.tutorials.mnist import input_data

def inputs():
    return input_data.read_data_sets('/tmp/data', one_hot=True)
