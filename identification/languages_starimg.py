import numpy as np

class languages_starimg:

    def __init__(self, image_info):
        self.image_info = image_info
        self.image = np.zeros((28,28))
        for rowndx in range(len(self.image_info)):
            self.image[int(self.image_info[rowndx,0]), int(self.image_info[rowndx,1])] = 1.0

    def print_image_info(self):
        np.set_printoptions(linewidth=200)
        print(self.image_info)

