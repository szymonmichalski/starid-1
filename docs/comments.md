*starid*

demonstration, testing, and evaluation

*lb a* uses a convolutional network with training and evaluation input files based on the classic mnist format. systems that process classic mnist are compatible.

*rb a* uses triangular structure in the star image.

*main processing loop*

*image viewer*

shows 28 x 28 mnist style star images.

*model*

tensorflow graph implementing inference for star identification. it's kept separate and independent since it's used by multiple scripts, for example lb, learn, and testing.

*training*

performs training of the model.

*evaluation*

performs evaluation of the model. star identification is performed on a group of images and the results are scored.

*rules based heuristic star identification*

given an input image of a star pattern, output an integer identifying the star at the center using methods based on geometry, pairs, triangles, etc. the transformation from the input x to the output y is rather direct and deterministic, but noise in the input complicates things. in particular, loss of angular resolution due to position quantization is effectively a large noise source.

*star identifier*

find star triangles in the image, and candidate stars that meet the constraints implicit within the triangle. these constraints are effectively the rules for candidate stars. for example, if a triangle consists of star pairs ab and bc, then the third side is ac.

*identify central star* this is the main function

*triangle*

represents a triangle as three constrained sides ab, bc, ca. travel around the sides ab to bc to ca so star pairs are not duplicated. traveling ac to cb to ba, you get the same pairs backwards.

*close loops abca* travel around sides connecting by pairs.

*close loops abda* travel around sides connecting by pairs.

*triangle side*

for adding, finding, removing, etc star pairs to a triangle side. one objective here is to work with maps of unique star keys, one key per star, rather than maps with multiple keys per star. this means using unordered_map, not unordered_multimap.

*stars* each star is a map key whose value is a map of star keys it pairs with

*trim pairs* remove pairs that have value zero or are no longer stars. then remove stars that have no pairs.

*append iterations* append the iterations contained in another side

*stars*

sky representation and image generation

*sky*

sky representation as pointing vectors, with methods to get the stars near an arbitrary point.

*pointing vectors*

star representations as pointing vectors and binary images container on disk

*new image matrix* create an axi axj image matrix for the star, with a random yaw

*get pointing vectors* get pointing vector representation of an image

*pairs over whole sky*

star pairs with a separation angle within a given range.

*pairs map* each star is a map key whose value is a map of star keys it pairs with.

*init* creates the pairs data structures for all star pairs with a separation less than maximum angle.

*float int table*

data structure based on floats in a range, with hash map like characteristics

*globals*

global values

*star catalog*

nasa skymap star catalog

*imgop*

tensorflow op generating runtime star images and labels.

*constructor* interfaces with tensorflow, and loads the sky binary file needed to generate star images

*compute* called by tensorflow to perform op

