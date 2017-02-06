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

**triangles**

find star triangles in the image, and candidate stars that meet the constraints implicit within the triangle. these constraints are effectively the rules for candidate stars. for example, if a triangle consists of star pairs ab and bc, then the third side is ac.

*constraint* remove pairs from constraint sides. these are sides shared by two triangles.

*reduce2* remove star pairs that don't agree with both a constraint side and another side.

*reduce1* remove star pairs that don't agree with another side.

*stars in three sides* find stars that are present in sidea, sideb, and sidec.

*stars in two sides* find stars that are present in both sidea and sideb.

*merge stars* merge a group of stars into another group of stars

**triangle side**

for adding, finding, removing, etc star pairs to a triangle side.

**pairs over whole sky**

provides quick access to all of the star pairs within a given radius. the underlying data structure is a form of map or hash map for efficient searching.

