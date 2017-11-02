import numpy as np
import matplotlib.pyplot as plt
import math

class languages_starimg:

    def __init__(self, starndx, info):
        self.starndx = starndx # starndx of target star
        self.info = info
        # use info to generate a 28 by 28 image pixel matrix
        self.image = np.zeros((28,28))
        for rowndx in range(len(self.info)):
            self.image[int(self.info[rowndx, 0]), int(self.info[rowndx, 1])] = 1.0
        # starlist is for info ready for writing nouns, verbs, and sentences
        self.starlist = []

    def print_image_info(self):
        np.set_printoptions(linewidth=200)
        print(self.info)

    def plot_image(self):
        plt.matshow(-1 * self.image, cmap='Greys', interpolation='nearest')
        plt.show()

    def starlist_prepare(self):
        # pixel axj=row, pixel axi=col, starndx, radial distance
        self.starlist.append([0, 0, int(self.starndx), 0])
        for row in self.info:
            x = row[1] - 13.5
            y = 13.5 - row[0]
            # rounding of r because of low res pixels.
            # for a particular star, pixel r varies significantly with image yaw
            # ceil() so only target target star had r = 0
            r = math.ceil(math.sqrt(x**2 + y**2))
            self.starlist.append([int(row[0]), int(row[1]), int(row[2]), int(r)])
        # sort by r and starndx
        self.starlist = sorted(self.starlist, key = lambda x: (x[3], x[2]))

    def starlist_print(self):
        import pprint
        pprint.pprint(self.starlist)

