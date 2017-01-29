**learning based star identification**

given an image of a star pattern, identify the star at the center, using methods based on convolutional networks, support vector machines, etc. these require learning a model, and the transformation from the input x to the output y is complex compared to for example a matrix transformation y = Hx.

**rules based heuristic star identification**

uses methods based on geometry, pairs, triangles, pyramids, etc. the transformation from x to y can be direct and deterministic. noise complicates things, and image position quantization generates significant noise.

**further discussion**

comments linked below are generated from project source code.

related | link
----- | ---
comments | http://noahhsmith.github.io/starid/comments
references | http://noahhsmith.github.io/starid/references
blog | http://noahhsmith.github.io/starid/
discussion | http://stackoverflow.com/users/5716954/noah-smith

thanks to | link
----- | ---
tensorflow | http://github.com/tensorflow/tensorflow
armadillo | http://arma.sourceforge.net
eigen | http://eigen.tuxfamily.org/index.php
cereal| http://github.com/USCiLab/cereal
optionparser | http://optionparser.sourceforge.net

