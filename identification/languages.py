import numpy as np
import matplotlib.pyplot as plt
import operator, pprint

from identification.languages_starimg import Starimg
from libstarid.libstarid import Libstarid
libstarid = Libstarid()

class Vocabulary:
    
    def __init__(self):
        self.starndxs = []
        self.geom = {}
        self.ids = {}
        self.geom['<unk>'] = 1000
        self.geom['<s>'] = 1000
        self.geom['</s>'] = 1000
        self.ids['<unk>'] = 1000
        self.ids['<s>'] = 1000
        self.ids['</s>'] = 1000

    def update(self, sentences, starndx):
        self.starndxs.append([starndx, len(sentences)]) # number of unique sentences for this star
        for key, value in sentences.items():
            geom = value[1].split(' ')
            for word in geom:
                if word not in self.geom:
                    self.geom[word] = 1
                else:
                    self.geom[word] += 1
            ids = value[2].split(' ')
            for word in ids:
                if word not in self.ids:
                    self.ids[word] = 1
                else:
                    self.ids[word] += 1

def sentences_write(starndx, numsentences, verbose=False):
    sentences = {}
    for cnt in range(numsentences):
        info = libstarid.image_info(starndx=starndx)
        starimg = Starimg(starndx=starndx, info=info)
        if not starimg.lang: # too few stars
            continue
        keytxt = starimg.lang.sentence_geom + ' : ' + starimg.lang.sentence_ids
        if keytxt not in sentences:
            sentences[keytxt] = [1, starimg.lang.sentence_geom, starimg.lang.sentence_ids]
        else:
            sentences[keytxt][0] += 1
    if verbose:
        pprint.pprint(sorted(sentences.values(), key=lambda x: -x[0]))
    return sentences

if __name__ == '__main__':
    vocabulary = Vocabulary()
    for starndx in range(10):
        sentences = sentences_write(starndx=starndx, numsentences=1000, verbose=False)
        vocabulary.update(sentences=sentences, starndx=starndx)
    pprint.pprint(vocabulary.starndxs)
