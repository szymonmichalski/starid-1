<img src="docs/images/star4a.png" align="right" height="200" width="200"/><img src="docs/images/star4b.png" align="right" height="200" width="200"/>

[about](http://starid.org/about), [references](http://starid.org/references)

*stars* - image generation from the nasa skymap catalog - [guide](https://drive.google.com/file/d/0B50jA_ROMYdHRjF6VUhKTkxvU0U/view?usp=sharing), [catalog](https://drive.google.com/file/d/0B50jA_ROMYdHMTNoenMzYkpNdXc/view?usp=sharing)

*identification* - recurrent neural networks, convnets, triangular patterns and structure - [recurrent network](https://github.com/noahhsmith/starid/blob/master/identification/recurrent_minimalist.py), [experimental rnn](https://github.com/noahhsmith/starid/blob/master/identification/recurrent.py), [convnet](https://github.com/noahhsmith/starid/blob/master/identification/convolutional_minimalist.py), [experimental cnn](https://github.com/noahhsmith/starid/blob/master/identification/convolutional.py), [triangle heuristics](https://github.com/noahhsmith/starid/blob/master/identification/triangles.h)

<br>

*recurrent neural network* - rnns are about sequential processing and patterns in sequential data. they’re natural for time series and time varying systems. from an aerospace perspective, they’re analogous to kalman filtering.

*convolutional network* - with cnns, sequences and time are not a factor. they’re natural for images, and more analogous to batch least squares. 

*triangles* - find star triangles in the image, and candidate stars that meet the constraints implicit within the triangle. these constraints are effectively the rules for candidate stars. for example, if a triangle consists of star pairs ab and bc, then the third side is ac.