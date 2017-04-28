### *starid*
###
### demonstration and testing
###

import libstarid.libstarid as ls
import id.id

libstarid = ls.libstarid()
libstarid.load_pairs()

image = libstarid.image(starndx=1)
print(libstarid.id(image))
print(id.id.lb(image))


