import numpy as np
import matplotlib.pyplot as plt
from languages_starimg import languages_starimg
import libstarid.libstarid as ls
import operator, pprint
libstarid = ls.libstarid()

target = 3 # starndx of target star

strs = {}
for cnt in range(1000):
    info = libstarid.image_info(starndx=target)
    starimg = languages_starimg(starndx=target, info=info)
    # starimg.print_starlist()
    # starimg.plot_image()
    langgeo = starimg.lang.noun1.txtrep_geometric + ', ' + starimg.lang.noun2.txtrep_geometric
    langid = starimg.lang.noun1.txtrep_starids + ', ' + starimg.lang.noun2.txtrep_starids
    str = langgeo + ' : ' + langid
    if str not in strs:
        strs[str] = [1, langgeo, langid]
    else:
        strs[str][0] += 1
pprint.pprint(sorted(strs.values(), key=lambda x: -x[0]))
