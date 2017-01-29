**learning based star identification**

given an input image of a star pattern, output an integer identifying the star at the center using methods based on convolutional networks, support vector machines, etc. these methods require learning a model and the transformation from the input x to the output y is a rather opaque black box compared to, for example, a matrix multiplication y = Hx.

**rules based heuristic star identification**

given an input image of a star pattern, output an integer identifying the star at the center using methods based on geometry, pairs, triangles, etc. the transformation from the input x to the output y is rather direct and deterministic, but noise in the input complicates things. in particular, loss of angular resolution due to position quantization is a significant noise source.

<br>

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

