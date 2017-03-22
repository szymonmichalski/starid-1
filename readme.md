<img src="docs/images/star4b.png" align="right" height="250" width="250"/> <img src="docs/images/star4a.png" align="right" height="250" width="250"/>

[notes](http://starid.org), [about](http://starid.org/about), and [related papers](http://starid.org/references)

*learning and rules based star identification*

identify stars using convnets and svms. feature selection for triangles and higher level geometry.

*stars*

star images, sky catalogs, serialized data structures, etc. the focus is on pointing vectors. pure representations of direction in space, with length normalized to one, pointing to positions on the sky. two coordinates are independent. these can be represented latlon-radec-ishly or xy-ishly in a plane tangent to the sky and its image in a sensor. the sky is a sphere formed by an infinite number of these pointing vectors. rotation about a pointing vector is an angle we’ll call yaw. looking at a star with your right arm pointed west, your line of sight is the star pointing vector and your arm is yaw zero. knowledge concerning a star image means an estimate and uncertainty for its pointing vector. our convention is that we're identifying a star at the center of the image. this means the image pointing vector is equivalent to the star pointing vector. the smaller the uncertainty of the image pointing vector, the more certain is our knowledge of the star pointing vector and its identity. when the image pointing vector is totally uncertain, we have the lost in space case.

thanks to [tensorflow](http://github.com/tensorflow/tensorflow), [armadillo](http://arma.sourceforge.net), [eigen](http://eigen.tuxfamily.org/index.php), [openblas](http://www.openblas.net/), [lapack](http://www.netlib.org/lapack/), [cereal](http://github.com/USCiLab/cereal), [optionparser](http://optionparser.sourceforge.net).
