### *starid*
###
### test and demo
###

import identification.id as id
import libstarid.libstarid as ls
libstarid = ls.libstarid()
libstarid.load_pairs()

image = libstarid.image(starndx=1)
print(libstarid.id(image))
print(id.cnn1(image))


