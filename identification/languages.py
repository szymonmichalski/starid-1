import numpy as np
import matplotlib.pyplot as plt
from languages_starimg import languages_starimg
import libstarid.libstarid as ls
import operator, pprint
libstarid = ls.libstarid()

target = 3 # starndx of target star

strs = {}
for cnt in range(100):
    info = libstarid.image_info(starndx=target)
    starimg = languages_starimg(starndx=target, info=info)
    # starimg.print_starlist()
    # starimg.plot_image()
    str = starimg.lang.noun1.txtrep_geometric + ' ' + starimg.lang.noun1.txtrep_starids
    if str not in strs:
        strs[str] = 1
    else:
        strs[str] += 1
pprint.pprint(sorted(strs.items(), key=lambda x: -x[1]))
