<img src="docs/images/nouns and verbs level0.png" align="right" width="426" height="202"/>

[references](http://starid.org/references), [about](http://starid.org/about)

*stars* image generation from the nasa skymap catalog, [skymap description](https://drive.google.com/file/d/0B50jA_ROMYdHRjF6VUhKTkxvU0U/view?usp=sharing), [skymap full text file](https://drive.google.com/file/d/0B50jA_ROMYdHMTNoenMzYkpNdXc/view?usp=sharing). our baseline sky is 8876 stars brighter than visual magnitude 6.5, roughly the sky a person sees.  [skymap text file](https://raw.githubusercontent.com/noahhsmith/starid/master/stars/skymap.txt) has the catalog rows for just these stars. [skymap csv file](https://raw.githubusercontent.com/noahhsmith/starid/master/stars/skymap.csv) provides some parsing of the fixed width rows to make skymap, hd, hr, and common name identifiers more accessible.

*identification* [recurrent neural networks](https://github.com/noahhsmith/starid/blob/master/identification/recurrent.py), [convolutional neural networks](https://github.com/noahhsmith/starid/blob/master/identification/convolutional.py), [triangular structures](https://github.com/noahhsmith/starid/blob/master/identification/triangles.cpp), [neural machine translation](https://www.linkedin.com/pulse/star-identification-translation-noah-smith/)

*recurrent neural networks* are natural for sequences and time varying systems. sequences may seem an indirect perspective for star images, but we're concerned with randomly rotated images. rotations shouldn't effect sequences beyond a phase offset, and recurrent networks were quickly able to identify thousands of stars.

*convolutional networks* are about static unchanging patterns. this seems to be a direct approach, but our star images are randomly rotated. for a given star, comparison of two patterns is complicated by their relative rotation.

*triangular patterns and structure* starts with a set of star identities and iteratively sets aside those that can’t be correct until one remains.

<img src="docs/images/nouns and verbs.png" align="right" width="426" height="202"/>

*neural machine translation* transforms geometry recognition into language translation. given a sequence of symbols representing a star field, translate it into a sequence of symbols representing star identifications, using an encoder and decoder with an attention interface between. on the encoder side are symbols representing nouns, blue, and verbs, green. for distances 2.3, 5.1, 4.9 we could use the symbol 235149. on the decoder side are symbols built from numerical starids.
