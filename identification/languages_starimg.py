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
            self.starlist.append([starndx, int(row[0]), int(row[1]), x, y, r])
        self.starlist = sorted(self.starlist, key=lambda x: x[5]) # sorted(self.starlist, key = lambda x: (x[3], x[0])
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
        self.geom = self.noun1.geom + ', ' + self.noun2.geom
        self.ids = self.noun1.ids + ', ' + self.noun2.ids

# each noun has two txt representations, geometric and starids
class lang1_noun:
    def __init__(self, stars):
        self.stars = stars # star input for just this noun, three stars
        id = [self.stars[0][0], self.stars[1][0], self.stars[2][0]]
        x = [self.stars[0][3], self.stars[1][3], self.stars[2][3]]
        y = [self.stars[0][4], self.stars[1][4], self.stars[2][4]]
        side01 = math.sqrt((x[0] - x[1])**2 + (y[0] - y[1])**2)
        side12 = math.sqrt((x[1] - x[2])**2 + (y[1] - y[2])**2)
        side20 = math.sqrt((x[2] - x[0])**2 + (y[2] - y[0])**2)
        sides = [
            [0, 1, id[0], id[1], math.ceil(side01 / 4.), x[0], y[0], x[1], y[1]],
            [1, 2, id[1], id[2], math.ceil(side12 / 4.), x[1], y[1], x[2], y[2]],
            [2, 0, id[2], id[0], math.ceil(side20 / 4.), x[2], y[2], x[0], y[0]]]
        sides = sorted(sides, key=lambda side: (side[4], side[0])) # increasing side length
        sideab = str(sides[0][4])
        sidebc = str(sides[1][4])
        sideca = str(sides[2][4])
        if (sides[0][0] == 0 and sides[1][0] == 1) \
                or (sides[0][0] == 1 and sides[1][0] == 2) \
                or (sides[0][0] == 2 and sides[1][0] == 0):
            stara = str(sides[0][2])
            starb = str(sides[0][3])
            starc = str(sides[1][3])
        else:
            stara = str(sides[0][3])
            starb = str(sides[0][2])
            starc = str(sides[1][2])
        self.sides = sides
        self.geom = 'n:' + sideab + ':' + sidebc + ':' + sideca
        self.ids = 'n:' + stara + ':' + starb + ':' + starc

