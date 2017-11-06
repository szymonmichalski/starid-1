import numpy as np
import matplotlib.pyplot as plt
import operator, pprint

from identification.languages_starimg import Starimg
from libstarid.libstarid import Libstarid

def sentences(starndx, numsentences, verbose=False):
    libstarid = Libstarid()
    sentencesdict = {}
    for cnt in range(numsentences):
        info = libstarid.image_info(starndx=starndx)
        starimg = Starimg(starndx=starndx, info=info)
        keytxt = starimg.lang.sentence_geom + ' : ' + starimg.lang.sentence_ids
        if keytxt not in sentencesdict:
            sentencesdict[keytxt] = [1, starimg.lang.sentence_geom, starimg.lang.sentence_ids]
        else:
            sentencesdict[keytxt][0] += 1
    if verbose:
        pprint.pprint(sorted(sentencesdict.values(), key=lambda x: -x[0]))

if __name__ == '__main__':
    sentences(starndx=3, numsentences=1000, verbose=True)
