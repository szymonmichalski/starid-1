<img src="docs/images/star4b.png" align="right" height="250" width="250"/><img src="docs/images/star4a.png" align="right" height="250" width="250"/>

[notes](http://starid.org), [about](http://starid.org/about), and [related papers](http://starid.org/references)

*learning based star identification*

tensorflow framework for identification of stars using convnets and svms.

*rules based star identification*

cpp for unique deterministic identification of triangular structure in tens of thousands of stars and millions of star pairs across the sky.

*stars*

star images, sky catalogs, serialized data structures, etc. the focus is on pointing vectors. pure representations of direction in space, with length normalized to one, pointing to positions on the sky. two coordinates are independent, and can be represented as ra and dec, or x and y in a plane tangent to the sky and its image in a sensor. the sky is a unit sphere formed by a continuum of pointing vectors. rotation about a pointing vector is an angle we’ll call yaw. looking at a star with your right arm pointed west, your line of sight is the star pointing vector and your arm is yaw zero. knowledge concerning a star image means an estimate and uncertainty for its pointing vector. our convention is that we're identifying a star at the center of the image. this means the image pointing vector is equivalent to the star pointing vector. the smaller the uncertainty of the image pointing vector, the more certain is our knowledge of the star pointing vector and its identity. when the image pointing vector is totally uncertain, we have the lost in space case.

thanks to [tensorflow](http://github.com/tensorflow/tensorflow), [armadillo](http://arma.sourceforge.net), [eigen](http://eigen.tuxfamily.org/index.php), [openblas](http://www.openblas.net/), [lapack](http://www.netlib.org/lapack/), [cereal](http://github.com/USCiLab/cereal), [optionparser](http://optionparser.sourceforge.net).
