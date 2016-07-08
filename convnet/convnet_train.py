
import numpy as np
import tensorflow as tf
import convnet

def train():
    convnet.go()

def main(argv=None):
    train()

if __name__ == '__main__':
    tf.app.run()
                            