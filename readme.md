<img src="docs/images/nouns and verbs level0.png" align="right" width="426" height="202"/>

[references](http://starid.org/references), [about](http://starid.org/about)

[*stars*](https://github.com/noahhsmith/starid/tree/master/stars) image generation from the nasa skymap catalog, [skymap description](https://drive.google.com/file/d/0B50jA_ROMYdHRjF6VUhKTkxvU0U/view?usp=sharing), [skymap full text](https://drive.google.com/file/d/0B50jA_ROMYdHMTNoenMzYkpNdXc/view?usp=sharing). our baseline sky is 8876 stars brighter than visual magnitude 6.5, roughly the sky a person sees.  [skymap text](https://raw.githubusercontent.com/noahhsmith/starid/master/stars/skymap.txt) has the catalog rows for just these stars. [skymap csv](https://raw.githubusercontent.com/noahhsmith/starid/master/stars/skymap.csv) provides some parsing of the fixed width rows to make skymap, hd, hr, and common name identifiers more accessible.

[*libstarid*](https://github.com/noahhsmith/starid/tree/master/libstarid) interfaces between numpy, tensorflow, eigen, etc

[*identification*](https://github.com/noahhsmith/starid/tree/master/identification) is the heart of the project.

[*recurrent neural networks*](https://github.com/noahhsmith/starid/blob/master/identification/rnn.py) are about sequences and time varying systems. there's less sensitivity to image rotation, beyond a phase offset.

[*convolutional neural networks*](https://github.com/noahhsmith/starid/blob/master/identification/cnn.py) are about static unchanging patterns. comparison is complicated by image rotation.

[*geometric structures*](https://github.com/noahhsmith/starid/blob/master/identification/triangles.cpp) starts with a set of star identities and iteratively sets aside those that can’t be correct geometrically, until one remains.

[*neural machine translation*](https://github.com/noahhsmith/starid/blob/master/identification/nmt.py) writes sentences about star images using a language about geometry, and translates these sentences into a language about star identifiers.
