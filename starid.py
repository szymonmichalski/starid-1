### *starid*
###
### demonstration, testing, and evaluation
###
import numpy as np
import tensorflow as tf
import libstars.libstars as ls
import id.id

libstars = ls.libstars()
libstars.load_pairs()

image = libstars.image(starndx=1)
print(libstars.id(image))
print(id.id.lb(image))


