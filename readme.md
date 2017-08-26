<img src="docs/images/linkedin cover 744 by 400.png" align="right"/>

[about](http://starid.org/about), [references](http://starid.org/references)

*stars* - image generation from the nasa skymap catalog - [skymap description](https://drive.google.com/file/d/0B50jA_ROMYdHRjF6VUhKTkxvU0U/view?usp=sharing), [skymap data file](https://drive.google.com/file/d/0B50jA_ROMYdHMTNoenMzYkpNdXc/view?usp=sharing)

*identification* - recurrent neural networks, convnets, triangular patterns and structure - [minimalist rnn](https://github.com/noahhsmith/starid/blob/master/identification/recurrent_minimalist.py), [recurrent network](https://github.com/noahhsmith/starid/blob/master/identification/recurrent.py), [minimalist cnn](https://github.com/noahhsmith/starid/blob/master/identification/convolutional_minimalist.py), [convolutional network](https://github.com/noahhsmith/starid/blob/master/identification/convolutional.py), [triangular patterns](https://github.com/noahhsmith/starid/blob/master/identification/triangles.cpp)

<br>

*recurrent neural networks* - recurrent networks are about patterns in sequential events. they’re natural for time series and time varying systems. sequences may seem an indirect perspective for star images, but we're concerned with randomly rotated images. rotations shouldn't effect sequences, and recurrent networks were quickly able to identify thousands of stars.

*convolutional networks* - convnets are about static unchanging patterns. this seems to be a direct approach, but our star images are randomly rotated. for a given star, comparison of two patterns is complicated by their relative rotation.

*triangular patterns and structure* - start with a set of star identities and iteratively set aside those that can’t be correct, until only one remains.
