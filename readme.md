<img src="docs/images/nouns and verbs level0.png" align="right" width="426" height="202"/>

[references](http://starid.org/references), [about](http://starid.org/about)

[*stars*](https://github.com/noahhsmith/starid/tree/master/stars) image generation from the nasa skymap star catalog.

[*libstarid*](https://github.com/noahhsmith/starid/tree/master/libstarid) interfaces between numpy, tensorflow, eigen, etc.

[*identification*](https://github.com/noahhsmith/starid/tree/master/identification) is the heart of the project.

[*geometric structures*](https://github.com/noahhsmith/starid/blob/master/identification/triangles.cpp) starts with a set of star identities and iteratively sets aside those that can’t be correct geometrically, until one remains.

[*convolutional neural networks*](https://github.com/noahhsmith/starid/blob/master/identification/cnn.py) are about static unchanging patterns.

[*recurrent neural networks*](https://github.com/noahhsmith/starid/blob/master/identification/rnn.py) are focused on sequences and time varying systems. it's possible to reduce sensitivity to image rotation.

[*neural machine translation*](https://github.com/noahhsmith/starid/blob/master/identification/nmt.py) writes sentences about star images using a language about geometry, and translates these sentences into a language about star identities. this can be insensitive to image rotation.
