<img src="docs/images/nouns and verbs level0.png" align="right" width="426" height="202"/>

[references](http://starid.org/references), [about](http://starid.org/about)

*stars* image generation from the nasa skymap catalog, [skymap description](https://drive.google.com/file/d/0B50jA_ROMYdHRjF6VUhKTkxvU0U/view?usp=sharing), [skymap full text file](https://drive.google.com/file/d/0B50jA_ROMYdHMTNoenMzYkpNdXc/view?usp=sharing). our baseline sky is 8876 stars brighter than visual magnitude 6.5, roughly the sky a person sees.  [skymap text file](https://raw.githubusercontent.com/noahhsmith/starid/master/stars/skymap.txt) has the catalog rows for just these stars. [skymap csv file](https://raw.githubusercontent.com/noahhsmith/starid/master/stars/skymap.csv) provides some parsing of the fixed width rows to make skymap, hd, hr, and common name identifiers more accessible.

*identification* is the heart of the project.

[*recurrent neural networks*](https://github.com/noahhsmith/starid/blob/master/identification/recurrent.py) are natural for sequences and time varying systems. sequences may seem an indirect perspective for star images, but we're concerned with randomly rotated images. rotations shouldn't effect sequences beyond a phase offset, and recurrent networks were quickly able to identify thousands of stars.

[*convolutional neural networks*](https://github.com/noahhsmith/starid/blob/master/identification/convolutional.py) are about static unchanging patterns. this seems to be a direct approach, but our star images are randomly rotated. for a given star, comparison of two patterns is complicated by their relative rotation.

[*geometric structures*](https://github.com/noahhsmith/starid/blob/master/identification/triangles.cpp) starts with a set of star identities and iteratively sets aside those that can’t be correct geometrically, until one remains.

[*neural machine translation*](https://www.linkedin.com/pulse/star-identification-translation-noah-smith/) focuses on writing sentences about star images using custom languages, lang1, lang2, lang3, etc, and evolving a language pair, for example lang37 and lang51, that's effective at representing geometric structure and star identifiers on the encoder and decoder sides of neural machine translation.
