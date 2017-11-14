<img src="docs/images/nouns and verbs level0.png" align="right" width="426" height="202"/>

[references](http://starid.org/references), [about](http://starid.org/about)

[*stars*](https://github.com/noahhsmith/starid/tree/master/stars) image generation from the nasa skymap star catalog.

[*libstarid*](https://github.com/noahhsmith/starid/tree/master/libstarid) interfaces between numpy, tensorflow, eigen, etc.

[*identification*](https://github.com/noahhsmith/starid/tree/master/identification) is the heart of the project.

[*triangles*](https://github.com/noahhsmith/starid/blob/master/identification/triangles.cpp) recurrently sets sets aside star identities that disagree geometrically, until only one remains.

[*convolutional neural networks*](https://github.com/noahhsmith/starid/blob/master/identification/cnn.py) are about static patterns. these are sensitive to rotation.

[*recurrent neural networks*](https://github.com/noahhsmith/starid/blob/master/identification/rnn.py) are focused on sequential patterns. it's possible to reduce sensitivity to rotation.

[*neural machine translation*](https://github.com/noahhsmith/starid/blob/master/identification/nmt.py) writes sentences about star patterns using a geometrical language, and translates these sentences into an identifier language. this can be insensitive to rotation.
