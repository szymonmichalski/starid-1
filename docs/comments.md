# learning
**learning based star identification**

given an input image of a star pattern, output an integer identifying the star at the center using methods based on convolutional networks, support vector machines, etc. these methods require learning a model and the transformation from the input x to the output y is a rather opaque black box compared to, for example, a matrix multiplication y = Hx.

**model**

tensorflow graph implementing inference for star identification. it's kept separate and independent since it's used by multiple scripts, for example lb, learn, and testing.

**learning**

performs training of the model.

**testing**

performs testing of the model. star identification is performed on a group of images and the results are scored.

# heuristics
**rules based heuristic star identification**

given an input image of a star pattern, output an integer identifying the star at the center using methods based on geometry, pairs, triangles, etc. the transformation from the input x to the output y is rather direct and deterministic, but noise in the input complicates things. in particular, loss of angular resolution due to position quantization is effectively a large noise source.

