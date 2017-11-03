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
        # self.starlist.append([int(self.starndx), 0., 0., 0.])
        # todo check pixels are unique within starlist
        for row in self.info:
            starndx = int(row[2])
            x = row[1] - 13.5
            y = 13.5 - row[0]
            r = math.ceil(math.sqrt(x**2 + y**2) * 100.) / 100.
            self.starlist.append([starndx, x, y, r])
        self.starlist = sorted(self.starlist, key = lambda x: (x[3])) # sorted(self.starlist, key = lambda x: (x[3], x[0])
        self.lang = lang1(self.starlist)

    def plot_image(self):
        plt.matshow(-1 * self.image, cmap='Greys', interpolation='nearest')
        plt.show()

    def print_starlist(self):
        import pprint
        pprint.pprint(self.starlist)

class lang1:
    def __init__(self, starlist):
        self.noun1 = lang1_noun(starlist[0:3])
        self.noun2 = lang1_noun(starlist[3:6])

# each noun has two txt representations, geometric and starids
class lang1_noun:
    def __init__(self, nounstarlist):
        self.nounstarlist = nounstarlist # star input for just this noun
        # use nounstarlist to update the two txt representations
        self.txtrep_geometric = 'na'
        self.txtrep_starids = 'na'
        self.txtreps_valid = False # set true if both reps are ok

