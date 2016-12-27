import numpy as np
import mnist
images = mnist.read_images('/home/noah/dev/starid/data/images_b1.mnist')
labels = mnist.read_labels('/home/noah/dev/starid/data/images_b2.mnist')
print (np.array_str(images[0,:,:,0], max_line_width=500))
starndxs = 800 * (labels + 1)
print (np.array_str(starndxs[0:25], max_line_width=500))
