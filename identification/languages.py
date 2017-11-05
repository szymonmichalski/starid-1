import numpy as np
import matplotlib.pyplot as plt
from languages_starimg import languages_starimg
import libstarid.libstarid as ls
import operator, pprint
libstarid = ls.libstarid()

target = 3 # starndx of target star

examples = {}
for cnt in range(1000):
    info = libstarid.image_info(starndx=target)
    starimg = languages_starimg(starndx=target, info=info)
    # starimg.print_starlist()
    # starimg.plot_image()
    
    example = starimg.lang.geom + ' : ' + starimg.lang.ids
    if example not in examples:
        examples[example] = [1, starimg.lang.geom, starimg.lang.ids]
    else:
        examples[example][0] += 1

pprint.pprint(sorted(examples.values(), key=lambda x: -x[0]))
