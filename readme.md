<img src="docs/images/star4b.png" align="right" height="250" width="250"/><img src="docs/images/star4a.png" align="right" height="250" width="250"/>

[notes](http://starid.org), [about](http://starid.org/about), [related papers](http://starid.org/references), [code notes](http://starid.org/comments)

*lb learning based starid*

tensorflow framework for identification using convolutional and recurrent networks.

*rb heuristic rule based starid*

cpp for deterministic identification using triangular structure.

*libimgop*

tensorflow op for star images.

*libstars*

pybind11 interface for star images.

*stars*

cpp sky representation and image generation. the focus is on pointing vectors. pure representations of direction in space, with length normalized to one, pointing to positions on the sky. two coordinates are independent and expressed in a plane tangent to the sky, and its image in a sensor. rotation about a pointing vector is yaw. we're identifying a star at the center of an image. the image pointing vector is equivalent to the star pointing vector. when the image pointing vector is totally uncertain, we have the lost in space case.

thanks to [tensorflow](http://github.com/tensorflow/tensorflow), [eigen](http://eigen.tuxfamily.org/index.php), [pybind11](https://github.com/pybind/pybind11), [armadillo](http://arma.sourceforge.net), [openblas](http://www.openblas.net/), [lapack](http://www.netlib.org/lapack/), [cereal](http://github.com/USCiLab/cereal), [optionparser](http://optionparser.sourceforge.net).
