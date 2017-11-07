import numpy as np
import matplotlib.pyplot as plt
import math

def diststr(x):
    return str(math.ceil(x / .1))

class Starimg:

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
        if len(self.starlist) < 6: # too few stars
            self.lang = None
            return
        self.lang = Lang1(self.starlist, self.starndx)

    def plot_image(self):
        plt.matshow(-1 * self.image, cmap='Greys', interpolation='nearest')
        plt.show()

    def print_starlist(self):
        import pprint
        pprint.pprint(self.starlist)

class Lang1:

    def __init__(self, starlist, starndx):
        self.noun0g = 'n:na'
        self.noun0i = 'n:' + str(starndx)
        self.noun1 = self.Noun(starlist[0:3])
        self.noun2 = self.Noun(starlist[3:6])
        self.verb1 = self.Verb(self.noun1)
        self.verb2 = self.Verb(self.noun1, self.noun2)
        self.sentence_geom = self.noun1.geom + ' ' + self.verb1.geom + ' ' + self.noun0g + ' , ' \
                             + self.verb2.geom + ' ' + self.noun2.geom + ' .'
        self.sentence_ids = self.noun1.ids + ' ' + self.verb1.ids + ' ' + self.noun0i + ' , ' \
                            + self.verb2.ids + ' ' + self.noun2.ids + ' .'

    class Verb:

        def __init__(self, nouna, nounb=None):
            xa = [nouna.sides[0][5], nouna.sides[1][5], nouna.sides[2][5]]
            ya = [nouna.sides[0][6], nouna.sides[1][6], nouna.sides[2][6]]
            xb = [0., 0., 0.]
            yb = [0., 0., 0.]
            if nounb:
                xb = [nounb.sides[0][5], nounb.sides[1][5], nounb.sides[2][5]]
                yb = [nounb.sides[0][6], nounb.sides[1][6], nounb.sides[2][6]]
            d0 = math.sqrt((xa[0] - xb[0]) ** 2 + (ya[0] - yb[0]) ** 2)
            d1 = math.sqrt((xa[1] - xb[1]) ** 2 + (ya[1] - yb[1]) ** 2)
            d2 = math.sqrt((xa[2] - xb[2]) ** 2 + (ya[2] - yb[2]) ** 2)
            self.geom = 'v:' + diststr(d0) + ':' + diststr(d1) + ':' + diststr(d2)
            self.ids = self.geom

    class Noun:

        def __init__(self, stars):
            self.stars = stars # star input for just this noun, three stars
            id = [self.stars[0][0], self.stars[1][0], self.stars[2][0]]
            x = [self.stars[0][3], self.stars[1][3], self.stars[2][3]]
            y = [self.stars[0][4], self.stars[1][4], self.stars[2][4]]
            side01 = math.sqrt((x[0] - x[1])**2 + (y[0] - y[1])**2)
            side12 = math.sqrt((x[1] - x[2])**2 + (y[1] - y[2])**2)
            side20 = math.sqrt((x[2] - x[0])**2 + (y[2] - y[0])**2)
            sides = [
                [0, 1, id[0], id[1], side01, x[0], y[0], x[1], y[1]],
                [1, 2, id[1], id[2], side12, x[1], y[1], x[2], y[2]],
                [2, 0, id[2], id[0], side20, x[2], y[2], x[0], y[0]]]
            sides = sorted(sides, key=lambda side: (side[4], side[0])) # increasing side length
            sideab = sides[0][4]
            sidebc = sides[1][4]
            sideca = sides[2][4]
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
            self.geom = 'n:' + diststr(sideab) + ':' + diststr(sidebc) + ':' + diststr(sideca)
            self.ids = 'n:' + stara + ':' + starb + ':' + starc
