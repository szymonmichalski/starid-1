<img src="docs/images/star4b.png" align="right" height="250" width="250"/> <img src="docs/images/star4a.png" align="right" height="250" width="250"/>

[discussion](http://starid.org), [comments](http://starid.org/comments) from source code, related [documents](http://starid.org/references), [photos](http://photos.starid.org), and a little [history](http://starid.org/about).

*learning and rules based star identification*

identify stars using convnets and svms. feature selection for triangles and higher level geometry.

*stars*

star images, sky catalogs, serialized data structures, etc. the focus is on pointing vectors. pure representations of direction in space, with length normalized to one, pointing to positions on the sky. they’re three dimensional, and with the unit constraint only two coordinates are significant. these can be expressed as latitude and longitude, right ascension and declination, or x and y in a plane tangent to the sky and its image in a sensor. the sky is a sphere formed by an infinite number of these pointing vectors. rotation about a pointing vector is an angle we’ll call yaw. face south with your right arm pointed west and look up at a star. your line of sight is the star pointing vector and your right arm is at zero yaw. knowledge concerning a star image means an estimate and uncertainty for its pointing vector. our convention is that the primary star to be identified is at the center of the image, so the image pointing vector is equivalent to the star pointing vector. the smaller the uncertainty of the image pointing vector, the more certain is our knowledge of the star pointing vector and its identity. when the image pointing vector is totally uncertain, we have the lost in space case.

thanks to [tensorflow](http://github.com/tensorflow/tensorflow), [armadillo](http://arma.sourceforge.net), [eigen](http://eigen.tuxfamily.org/index.php), [openblas](http://www.openblas.net/), [lapack](http://www.netlib.org/lapack/), [cereal](http://github.com/USCiLab/cereal), [optionparser](http://optionparser.sourceforge.net).
