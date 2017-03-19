**learning based star identification**

given an input image of a star pattern, output an integer identifying the star at the center using methods based on convolutional networks, support vector machines, etc. these methods require learning a model and the transformation from the input x to the output y is a rather opaque black box compared to, for example, a matrix multiplication y = Hx.

**model**

tensorflow graph implementing inference for star identification. it's kept separate and independent since it's used by multiple scripts, for example lb, learn, and testing.

**learning**

performs training of the model.

**testing**

performs testing of the model. star identification is performed on a group of images and the results are scored.

**rules based heuristic star identification**

given an input image of a star pattern, output an integer identifying the star at the center using methods based on geometry, pairs, triangles, etc. the transformation from the input x to the output y is rather direct and deterministic, but noise in the input complicates things. in particular, loss of angular resolution due to position quantization is effectively a large noise source.

**star identifier**

find star triangles in the image, and candidate stars that meet the constraints implicit within the triangle. these constraints are effectively the rules for candidate stars. for example, if a triangle consists of star pairs ab and bc, then the third side is ac.

*identify central star* this is the main function

**triangle**

represents a triangle as three constrained sides ab, bc, ca. travel around the sides ab to bc to ca so star pairs are not duplicated. traveling ac to cb to ba, you get the same pairs backwards.

*close loops abca* travel around sides connecting by pairs.

*close loops abda* travel around sides connecting by pairs.

**triangle side**

for adding, finding, removing, etc star pairs to a triangle side. one objective here is to work with maps of unique star keys, one key per star, rather than maps with multiple keys per star. this means using unordered_map, not unordered_multimap.

*stars* each star is a map key whose value is a map of star keys it pairs with

*trim pairs* remove pairs that have value zero or are no longer stars. then remove stars that have no pairs.

*append iterations* append the iterations contained in another side

**pairs over whole sky**

star pairs with a separation angle within a given range.

*pairs map* each star is a map key whose value is a map of star keys it pairs with.

*init* creates the pairs data structures for all star pairs with a separation less than maximum angle.

