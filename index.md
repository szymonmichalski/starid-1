# 07.01.2017

more automation with the the mnist style dataset

    /usr/bin/python3.5 /home/noah/dev/starid/system.py

n 100 | ok | t
------ | ------ | -----
lb | 0.500 | 0.548
rb | 0.900 | 0.334

# 05.01.2017

serialized sky and pairs

disk serialization of these two classes is now full integrated and performance delta is clear - here's on a six year old laptop

    /usr/bin/python3.5 /home/noah/dev/starid/system.py
    lb 1.668 seconds
    rb 0.329 seconds - had been around 7 seconds
    true identity 800
    learning-based identification 800
    rules-based identification 800

runtime of rb was reduced by more than an order of magnitude - from about seven seconds to less than half a second. sky file is 2mb and pairs file is 5mb. here's on a two year old desktop

    /usr/bin/python3.5 /home/noah/dev/starid/system.py
    lb 0.309 seconds
    rb 0.200 seconds
    true identity 800
    learning-based identification 800
    rules-based identification 800

# 04.01.2017

cereal and optionparser. with initial functionality in place, it's time for a round of refactoring and performance. two cpp header-only libraries have jumped in and they're giving a pretty good feeling about the state of modern cpp.

cereal has quickly allowed two classes, representing the complete sky and all star pairs, to be streamed to and from disk. this is an order of magnitude improvement over runtime generation - say from six seconds to half a second on a six year old laptop. optionparser has taken some pain out of command line handling.

http://optionparser.sourceforge.net/

https://github.com/USCiLab/cereal

# 03.01.2017

names matter

cpp caused some unnecessary pain last night - working on serializing the pairs over whole sky object, things were going smoothly

    #include <cereal/types/string.hpp> for strings
    #include <cereal/types/tuple.hpp> for tuples
    #include <cereal/types/vector.hpp> for vectors
    #include <cereal/types/unordered_map.hpp> for unordered maps
    #include <cereal/types/pair.hpp> for pairs... right?

wrong.

    #include <cereal/types/utility.hpp> for pairs

and it's not cereals fault. cpp puts std::pair in utility.

# 29.12.2016

r2016c new release on github. system is working - rules-based and learning-based subsystems are functioning

    /usr/bin/python3.5 /home/noah/dev/starid/system.py
    true identity 1600
    learning-based identification 1600
    rules-based identification 1600

lb is using convnet in tensorflow. rb is using triangles in cpp.

# 27.12.2016

initial convnet predictions as part of establishing an overall system for parallel evolution of triangles and convnet, there was a first convnet evaluation run this morning. everything was mnist-style except using randomly yawed images of ten stars.

convnet identifications were right for 0.6 of the evaluation examples. pretty impressive for five minutes of naive training on a six year old laptop. and plenty of room for improvement.


26.12.2016

data formats

after some interesting experiences today, my picture is that tfrecords is natural within tensorflow, but with just numpy the mnist format is nice. this means keeping both types of files side by side for a given data set. tensorflow training with tfrecords, and numpy manipulation with mnist...


24.12.2016

complete baseline data on github

in preparation for creating a project level frontend for triangles cpp and infer tensorflow - all the baseline data files are now in the git repo.

ideally the frontend will quickly have an end to end demo acting as a system level test.


22.12.2016

ten star subset of skymap catalog

with brightness cutoff at mv 6.5 skymap gives - stars 8876, dim stars 290585, error_stars 0.

ten of these 8876 are used for testing - starndxs 800, 1600, 3200, ... 8000.

there's now a subset of the skymap catalog for faster initialization, containing just these ten. when using this subset - star 800 becomes star 0, star 1600 becomes star 1, ... star 8000 becomes star 9. also added a subset for the 8876 stars.


18.12.2016

r2016b

everything is working again in stars, triangles, and infer - r2016b tag created.

next step seems to be an evaluation framework for simultaneous development of triangles and infer - heuristic and machine learning approaches...


17.12.2016

float int table class

this returns to a discussion of the very specific type of algorithm and data structure used repeatedly in star id - a type of lookup table, bordering on a hash table.

there is a sorted vector of floats representing a physical quantity. each float has an associated int identifying a star. this a two column float and int table. the common usage is to search for all of the floats within a given range, from lower float to upper float.

representing this as it own class, there is plenty of room for search optimization. mortari's k-vector method for example takes this in a direction toward a hash table, with the indexes of lower float and upper float computed by equation.


7.8.2016

deconvnet

before experimenting with convnet models, a deconvnet should be implemented for insights into star pattern learning. this fits with the concept of impulse signals to understand convnet response, and heads in the direction of inverse problems.


5.8.2016

star pattern impulse signal

for randomly yawed 28 by 28 images of a star pattern, is there a pattern that could act as an impulse signal with a clean and understandable convnet response. it's likely either a star pair or triangle. the star separations are a critical factor, relating to local versus global features, filters, pooling, etc. maybe a right triangle with ratios 1 : 2 : sqrt(5) is a useful probe signal.


28.7.2016

starid data v1 available

baseline input data is here, starid_data_v1.tar.gz. every image has been randomly yawed, so the mnist stuff is non standard. *a.* files are 60k training images, *b.* files are 10k test images.

-rw-rw-r-- 1 noah noah 53460000 Jul 25 08:13 mnista.tfrecords

-rw-rw-r-- 1 noah noah 8910000 Jul 28 08:14 mnistb.tfrecords

-rw-rw-r-- 1 noah noah 53460000 Jul 28 08:49 starida.tfrecords

-rw-rw-r-- 1 noah noah 8910000 Jul 28 13:18 staridb.tfrecords

./mnist_format:

-rw-rw-r-- 1 noah noah 47040016 Jul 22 16:22 mnist_imagesa.mnist

-rw-rw-r-- 1 noah noah 7840016 Jul 28 08:12 mnist_imagesb.mnist

-rw-rw-r-- 1 noah noah 60008 Jul 22 16:22 mnist_labelsa.mnist

-rw-rw-r-- 1 noah noah 10008 Jul 28 08:12 mnist_labelsb.mnist

-rw-rw-r-- 1 noah noah 47040016 Jul 28 08:45 starid_imagesa.mnist

-rw-rw-r-- 1 noah noah 7840016 Jul 28 13:16 starid_imagesb.mnist

-rw-rw-r-- 1 noah noah 60008 Jul 28 08:45 starid_labelsa.mnist

-rw-rw-r-- 1 noah noah 10008 Jul 28 13:16 starid_labelsb.mnist


27.7.2016

yawed starid is working

yawed and unyawed versions of starid and mnist are working, so the input layer is essentially taken care of now and the focus changes to learning. an interesting possibility is packaging the data and code of the input layer in a standalone way for broader usability.


23.7.2016

yawed mnist is working

it finds non zero pixels and rotates their coordinates. there is a bit of aliasing for some rotation angles due to rounding of coordinates, but the result is essentially as expected - rotated mnist numerals. now to feed star patterns through the same processing.


17.7.2016

yawed mnist

the cpp example generator will be capable of creating yawed mnist as well as unyawed and yawed starid examples, all in mnist format. here's an example of filenames

mnist_unyawed_images.mnist

mnist_unyawed_labels.mnist

mnist_unyawed.tfrecords

mnist_yawed_images.mnist

minst_yawed_labels.mnist

mnist_yawed.tfrecords

starid_unyawed_images.mnist

starid_unyawed_labels.mnist

starid_unyawed.tfrecords

starid_yawed_images.mnist

starid_yawed_labels.mnist

starid_yawed.tfrecords

convnet output layer

for the nearly 9000 stars below mv 6.5, classification means a convnet with an output layer of nearly 9000 classes. this is more classes than seems to be common. at first ten stars are ok for testing using ten class mnist pipelines, but it will be interesting to see what happens as the number of stars and classes scale.


16.7.2016

mnist format

with code from eric yuan, mnist files are reading into cpp armadillo matrices. after adding code for writing back to mnist files, experiments can begin with both yawed mnist and star patterns. for identifying ten stars, any mnist pipeline should work. it would be nice to write directly to tfrecords files from cpp as well, but the python mnist to tfrecords converter is fine for now.


9.7.2016

throughput

with tensorflow a focus becomes throughput - for an arbitrary number of machines, cpus, and gpus - provide information at a rate that keeps everything busy over arbitrarily long runs. this is practical for starid. what's needed is a fast example generator.

the concept is to bypass the file system and directly feed in examples over the entire sky, random pointing and yaw, any limiting magnitude and field of view size, etc.



3.7.2016

big picture update

star model

l0 - hardware star sensor measurements

l1 - star pointing vectors in a sensor coordinate frame

l2 - star patterns

heuristic starid

pairs - l1 star pair angle matching

starid learning

svm - support vector machines

convnet - convolutional networks

l2 star patterns and mnist

10x10 and 100x100 star pattern grids are reasonable to experiment with. 10x10 is too small and 100x100 is too large. a choice between is too arbitrary. tensorflow makes it simple to work with conv nets and the mnist 28x28 dataset. so 28x28 it is. star patterns should fit into mnist tf models. an interesting path will be seeing how they handle arbitrarily rotated mnist images, equivalent to the yaw problem.


2.7.2016

global templates and local features

here's some interesting terminology from a 2004 image recognition paper. svm is about matching a global template. conv net is about matching local features. invariant features, such as a star pattern, are somewhere between or above the global template local feature axis.


27.6.2016

the yaw problem

say you're given a set of star vectors in the sensor coordinate frame and asked to identify one near the yaw axis. the other vectors are features, are a function of yaw, and at the same time represent an invariant pattern that can be learned.

old school is to normalize away yaw. this is error prone.

new school is to recognize the pattern regardless of yaw. convnet svm combinations should be capable of this.


22.6.2016

optimization

svm is about finding the minimum of alpha K alpha. its quadratic so there is one minimum. the concern is that K is a dense matrix that gets big with training set size.

old school is divide and conquer using smo for a sequence of simple-as-possible sub problems.

new school is using tensorflow for brute force with modern hardware - gpu, tpu, etc.


21.6.2016

svm classes

tensorflow jargon is nice and can be adopted here. two high level concepts are a model, and training a model. a model makes predictions and with training its predictions become better.

the two core svm classes are model and train. the pure cpp implemetation will focus on these two classes. the tensorflow implementation can try to use the model class and reimplement train as a tensorflow graph - possibly with a new cpp tf kernel.


11.6.2016

tensorflow

with svm well underway, interesting to note at this point that it looks like the next approach should be tensorflow. the name was new eight months ago. now it seems to be the natural lost-in-space tool - next generation matrix operations.



11.6.2016

svm train

the concept is to implement svm in parallel with libsvm using armadillo and modern cpp. the libsvm standard heart scale dataset can validate the new implementation. starting point is an svm train class.

hmmm, on closer examination, the heart scale data is riddled with null values, reflected in unusual formatting. null handling is a detour, so the heart scale dataset is out for now.


7.6.2016

big picture update

star model

l0 - unprocessed sensor measurements

l1 - pointing vectors in the sensor coordinate frame

l2 - feature vectors

star identification

ptq - pairs triads quads

star identity learning

knn - nearest neighbors

svm - support vector machines

tf - tensorflow


4.6.2016

sequential minimal optimization

looks like the focus for the initial svm implementation will be smo. for an aerospace person the svm focus on quadratic programming is as comfortable as home. the histories of kalman filtering and kernel machines could be an interesting topic to explore.

training examples and false stars

false stars are mostly about making interesting training examples for svm and ann development. with modern sensors they are rare in l2. they make learning much more interesting though, so we will increase their frequency. this could also be viewed as increasing robustness for lower performance and less expensive sensors.

for real sensors, false stars are a consideration, particularly in l0. the classical problem for spacecraft star trackers is cosmic rays hitting the detector and dust or debris in front of the optics. these are time varying. wait long enough and they go away. normally they are handled by the processing from l0 to l1.

but we can also imagine a phone camera pointed at the night sky. to go from l0 to l1, we have to pick the true stars out of the images.


3.6.2016

l1b parameters

l1a is ideal pointing vectors in the sensor frame, parameterized by

fov - field of view radius in arcseconds

mv - faintest star visual magnitude

l1b is more realistic pointing vectors in the sensor frame, adding the parameters

noise - pointing vector noise equivalent angle in arcseconds

false stars - gaussian distribution of false star counts


29.5.2016

l1a and l1b

as part of creating training examples, modelling sensor noise and errors becomes more important. this is reflected in l1b.

l1a is ideal three dimensional star pointing vectors in the sensor frame.

l1b adds pointing noise and false stars.


28.5.2016

feature vector tradeoff

for generating training sets, it's good to clarify that the feature vector is based on knowing, for a given star and sensor, the nearest observable neighbor. this allows the feature vector to be independent of yaw.

this is fine for l1 and l2. l0 is complicated by variable sensitivity.


16.5.2016

training class in base

fundamental concepts currently represented in the base build are catalog, sensor, and pointing.

with parallel training of knn, svm, and ann beginning, it becomes a fourth fundamental concept.

svm kernel selection

to begin with the minimal svm kernel, simple dot products between feature vectors, should be sufficient. a nonlinear kernel example would be useful for comparison. possibly a gaussian kernel.

it also seems likely there will not be performance problems using a batch mode implementation with n = 100 inputs. possibly an on-line implementation should follow.


14.5.2016

number of ann hidden neurons

the current picture is to try an n = 100 feature vector as input, representing a ten by ten grid pattern. the number of outputs is one, binary classification.

for ann a rough guide is that for m outputs and n inputs, the hidden layer can have about sqrt(mn) = 10 neurons. this give a network with a nice 100 - 10 - 1 structure. on the other hand, the idea is to start with as few hidden neurons as possible. start with what is known to be too few, and increase their number only as needed. this suggests a 100 - 5 - 1 or 100 - 2 - 1 structure to start with.


13.5.2016

simple knn working

end to end knn unit test added, now turning to svm and ann.


11.5.2016

simple approach for knn

for a given feature vector, the nearest neighbors have the largest dot products. all dot products are from zero to one here since the feature vector components are positive or zero. the simple approach is k = 1 and the input feature vector is classified with the training feature vector having the largest dot product.


8.5.2016

paths to l2

l0 - unprocessed sensor measurements

l1 - pointing vectors in sensor frames and the celestial frame

l2 - feature vectors

approaches

ptq - pointing vector classification using star pair angular separations

knn - feature vector classification using k nearest neighbors

svm - feature vector classification using support vector machines

ann - feature vector classification using artificial neural networks

current emphasis is on vectorized processing using blas. concurrency can follow.


5.5.2016

feature vector size

the first questions for knn seem to be feature vector size. for

case a - 10 by 10 grid so 100 features

case b - 100 by 100 grid so 10000 features

is case a good enough for distinguishing 8876 stars brighter than mv 6.5?

is case b practical performance-wise?

histograms of feature counts for 8876 feature vectors. bins are 0-5, 5-10, 10-15, etc.

case a - 104 4081 3192 1142 297 58  2  0  0 0

case b - 92  3565 3129 1365 407 190 91 30 5 2

histograms of dot products between 8876 normalized feature vectors. bins are 0-0.1, 0.1-0.2, 0.2-0.3, etc.

a - 6712609  14730674 12653854 4543313 694507 49639 2523 114 11 4

b - 30004395 9117682  258869   5973    317    9     2    1   1  0

case b feature vectors are more distinct, as expected.


1.5.2016

levels 0, 1, 2

sensor data abstracts nicely as

level 0 - unprocessed measurements, hardware level

level 1 - pointing vectors

level 2 - feature vectors

we're interested in levels 1 and 2. mostly level 2...


27.4.2016

feature vectors

it makes sense to add feature vectors to the base as part of sensor obs. a feature vector can represent a grid over observation tangent plane coordinates. an n by n grid of zeros and ones means an n^2 feature vector and feature space.

there's a tradeoff between resolution and dimensionality. for a four degree radius and magnitude limit around seven, so maybe 10 to 50 stars in the field of view, n = 10 or 100 seem possible...


24.4.2016

things to consider

https://en.wikipedia.org/wiki/Feature_vector

https://en.wikipedia.org/wiki/K-nearest_neighbors_algorithm

https://en.wikipedia.org/wiki/Multilayer_perceptron

https://en.wikipedia.org/wiki/Support_vector_machine

pairs and triads are working

pairs based triad identification is working. now to include quads for validation.

serious thinking began yesterday for machine learning builds in patterns and neuralnets. one concept is a grid pattern representing the sky around a given star. a rule makes the grid independent of yaw. in physical terms this is about defining tangent planes on the sky. use the nearest neighbor star, the nearest bright star, etc.


23.4.2016

tolerance for triads

things are simpler if the candidate sets id(ab), id(ac), id(bc) do not overlap. this is true if the angles ab, ac, and bc are sufficiently different. the current criteria is that they differ by an arcminute or more.


20.4.2016

pairs triplets quadruplets concept

given three unit vectors a, b, c and a function id() that returns a list of candidate ids...

if

id(ab) and id(ac) have id1

id(ba) and id(bc) have id2

id(ca) and id(cb) have id3

and for a fourth unit vector d

id(ab) and id(ac) and id(ad) have id1

id(ba) and id(bc) and id(bd) have id2

id(ca) and id(cb) and id(cd) have id3

and for a fifth unit vector e

id(ab) and id(ac) and id(ad) and id(ae) have id1

id(ba) and id(bc) and id(bd) and id(be) have id2

id(ca) and id(cb) and id(cd) and id(ce) have id3

... etc...

and if

id(ad) and id(bd) and id(cd) have id4...

and if

id(ae) and id(be) and id(ce) have id5...

... etc...


18.4.2016

triplets class

given an observation of n stars, what sequence of pairs or triplets best leads to a pairs based identification?

mortari addresses this in his 2004 paper with a sequence of triplets that jump around the field of view, making a breadth first search rather than a depth first search.

this can be represented as a triplets class. given n stars it returns a breadth first sequence of triplets.


16.4.2016

pairs method

ready to implement pairs based method. common terminology includes triangles for three stars, pyramids for four stars.

a build for pairs is added alongside the builds for base and gtest. placeholder builds for patterns and neuralnets are also added.


14.4.2016

sensor class ready

onward to the first star identification implementation...


9.4.2016

sensor class and obs struct

sensor class now has a pointing vector and yaw constructor, a member attitude, and support for rotation vectors, rotation matrices, and quaternions.

for observed stars, return an obs struct with both ideal values and measurement errors.


5.4.2016

sensor class, geometry, cpp linear algebra library

a sensor class means multiple reference frames, rotations, and representations of unit vectors, so a linear algebra library becomes necessary here. i've mostly used armadillo and a bit of eigen and gnu scientific library. time for a quick review of the field.

just glancing at the wikipedia page for linear algebra libraries, eigen and armadillo are the choices.

the matlab orientation of armadillo decides it - continue with armadillo.


3.4.2016

sensor class

now that the sky is in place, time to create a sensor.

sensor class is based on the pinhole camera model.

first-order characteristics are attitude, sensitivity, and field-of-view.

unit vectors are the representation for stars.

unit vector point on the sky and a yaw rotation are a useful representation for attitude here, particularly in the constructor, and are reinterpreted as a rotation matrix or quaternion as needed.

tangent plane coordinates are the representation for field-of-view.

uncertainties will be modeled in the observation class. the sensor class models only the ideal truth.


2.4.2016

star pairs class first results

star pairs class is now working and first results for mv = 6.5 and radius = 4 degrees are

bright stars 8876 dim stars 290585

atable size 56585 med 2.79 max 3.99

so for ~9k bright stars there are ~56k neighbor pairs, and the pair separations in degrees have median 2.8 and max 4


31.3.2016

star pairs class

the star pairs class can be based on the concept of a star and its neighbors, applied sequentially to each of the significant stars in the catalog...

star pairs for the entire sky can be collected from these star objects into a main vector.

as pairs stream towards the main vector, duplicates can be removed using a hash table with a key string composed from both pair members.


28.3.2016

stars near some point on the sky is working

results from asking what is near a point near cassiopeia, with a mag 6.5 cutoff

2 AG+59 1670

8

20

23   9    Cas

34

37

49

56  11bet Cas

87

95

125  12    Cas

148

164  15kap Cas

8733

8788

8793

8811

8812   5tau Cas

8821

8822   6    Cas

8823

8825

8848   7rho Cas

8855

8865


26.3.2016

stars near some point on the sky

a function for the catalog class, the algorithm i've used for years came from a mortari paper. it uses lookup tables for the x, y, and z axes to create three rings or bands on the sky. here's some ring search matlab


25.3.2016

unix and j2000 timestamps

unix timestamp is seconds from Jan 1 00:00:00 1970

j2000 timestamp is seconds from Jan 1 00:00:00 2000

#define J2000_EPOCH_OFFSET 946684800

/** Converts a j2000 timestamp to a unix timestamp. */

static inline time_t j2000_to_unix_epoch(time_t j2000) {

 return j2000 + J2000_EPOCH_OFFSET;

}

/** Converts a unix timestamp to a j2000 timestamp. */

static inline time_t unix_epoch_to_j2000(time_t unix) {

 return unix - J2000_EPOCH_OFFSET;

}


24.3.2016

star pairs class and angle lookup

star pair angle lookup seems to be the clearest terminology for what is needed to search the star catalog.

early objectives are

a skymap star catalog class

a star pair class with angle lookup


20.3.2016

catalog class and skymap records

a skymap record is 523 bytes long, including two control bytes at the end. this matlab code picks out certain useful values. more are available as shown in the skymap specification.


19.3.2016

index search

some interesting comments from stackoverflow about lookup and hash tables

No, it is not conceptually correct to call a lookup table a hash table: in your case a lookup table is a simple array. Calling something a hash table implies certain behavior in cases when the hash function is not perfect (i.e. in the presence of hash collisions); arrays have none of this behavior, so calling this a "hash lookup" would likely mislead your listeners or readers.

In general, any kind of associative storage, including hash tables, various trees, and so on, can be used to perform lookup operations. In your case, the index of the array is associated with the value stored at that index, letting you look up the value in constant time.

or

Yes, if you accept Wikipedia's definition of hash table. Quoting from that definition:Ideally, the hash function should map each possible key to a unique slot index, but this ideal is rarely achievable in practice (unless the hash keys are fixed; i.e. new entries are never added to the table after it is created).

and

You can substitute all lookup tables by hash tables, but you can't substitute all hash tables by lookup tables. So yes, a lookup table can be considered to be a special form of a hash table, and a hash table can be considered to be a general form of a lookup table.

In a similar way, a list can be considered to be a special form of a 2D table (with a single column).

However, we are talking about software here. There are a gazillion different solutions to a given problem, and a gazillion different possibilities to build your data structures. For the example, with static size or dynamic growth, with required unique entries or with collision handling, with a fixed or a configurable hash function, etc. There are a lot of ways between a plain lookup table and a full hash table, without a clear border where you could say here it is this, but there it has become that.

However (again), when a specific data structure proves to be useful, it usually gets its own name. As was said here, with such a name there are associated expectations about the functionality. There may even be a strict definition about the required minimum functionality. If you want your code to be readable by others, you better stick to the known terms. Thus you should call your lookup table a lookup table, even though technically it is a special form of a hash table.


18.3.2016

a nice statement of the problem

mortari 2004

The star polygon geometric structure is defined by the set of M = n! / (n − 2)! 2! interstar angles associated with a spherical polygon set of n stars, such as pairs (n = 2), triangles (n = 3), as well as pyramids (n = 4). The spherical polygon is closely related to the usual polygon, where the straight line sides are replaced by great circle arcs (angles) on the surface of a unit sphere connecting the neighboring pairs of stars in a set of p stars. More specifically, the star pattern geometric structure for the purpose of star identification is defined by the set of M interstar angles {ϑij = ϑji = cos−1 (b T i bj )} measured between each distinct pair of the p lineof-sight vectors {(bi , bj ) : (i, j) ∈ {1, 2, . . . p}} that point from the sensor toward the vertices of the star spherical polygon on the celestial sphere. Note we adopt the convention that the measured line-of-sight unit vectors with components in the sensor body axes are denoted bi , whereas the corresponding line of sight vectors based on cataloged information with components in the inertial reference frame of the star catalog are denoted rI . The whole objective of star identification can be boiled down to finding the correspondence between indices (i) of measured stars and the indices (I) of cataloged stars.


16.3.2016

skymap catalog binary text file

a curious thing about the skymap catalog - it is a type of binary text file. each line contains a specified number of bytes per field, and each field has a type (int, string, etc). it's strongly-typed. it's exact memory layout is defined.

it could be equated to serialized objects of a cpp class.

probably the quicker approach for initial implementation is to view it just from a string handling perspective, but a later deserialization approach would be interesting.


13.3.2016

basic classes

catalog class

sensor class

observations class

identifications class
