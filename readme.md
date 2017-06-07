<img src="docs/images/star4a.png" align="right" height="200" width="200"/><img src="docs/images/star4b.png" align="right" height="200" width="200"/>

[about](http://starid.org/about), [references](http://starid.org/references)

*stars* - image generation from the nasa skymap catalog - [guide](https://drive.google.com/file/d/0B50jA_ROMYdHRjF6VUhKTkxvU0U/view?usp=sharing), [catalog](https://drive.google.com/file/d/0B50jA_ROMYdHMTNoenMzYkpNdXc/view?usp=sharing)

*identification* - recurrent neural networks, convnets, triangular patterns and structure - [recurrent network](https://github.com/noahhsmith/starid/blob/master/identification/recurrent_minimalist.py), [experimental rnn](https://github.com/noahhsmith/starid/blob/master/identification/recurrent.py), [convnet](https://github.com/noahhsmith/starid/blob/master/identification/convolutional_minimalist.py), [experimental cnn](https://github.com/noahhsmith/starid/blob/master/identification/convolutional.py), [triangle heuristics](https://github.com/noahhsmith/starid/blob/master/identification/triangles.h)

<br>

*recurrent neural networks* - recurrent networks are about patterns in sequential events. they’re natural for time series and time varying systems. sequences may seem an indirect perspective for star images, but we're concerned with randomly rotated images. rotations shouldn't effect sequences, and recurrent networks were quickly able to identify thousands of stars.

*convolutional networks* - convnets are about static unchanging patterns. this seems to be a direct approach, but our star images are randomly rotated. for a given star, you can't simply compare one image with another, without accounting for rotation.

*triangular patterns and structure* - find star triangles in the image, and stars that are possible for the triangles. the triangles imply rules for setting aside candidate stars that can't be correct. for a particular image, we start with thousands of candidates and set aside all but one.
