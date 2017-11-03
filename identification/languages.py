import numpy as np
import matplotlib.pyplot as plt
from languages_starimg import languages_starimg
import libstarid.libstarid as ls
libstarid = ls.libstarid()

target = 3 # starndx of target star

info = libstarid.image_info(starndx=target)
starimg = languages_starimg(starndx=target, info=info)
starimg.print_starlist()
starimg.plot_image()
