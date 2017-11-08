<img src="images/nouns and verbs level0.png" align="center" width="426" height="202"/>

[references](http://starid.org/references), [about](http://starid.org/about)

*8.11.2017*

nmt is learning to identify ten stars. and it learns fast, based on the first hello world style training. looks good.

*7.11.2017*

with vocabularies ready, next step is to prepare training, eval, and inference datasets. these can be text files of sentences in geometric and identifier languages. we'll use the newish tensorflow dataset iterator for input pipelines into three models in three graphs with three sessions for train, eval, infer.

our languages are simple and small. train, eval, and infer datasets are similar. individual image yaws are random, but the overall file structures are parallel. we'll mirror the baseline to ease comprehension, so separate files for each.

*6.11.2017*

neural machine translation [baseline framework](https://github.com/tensorflow/nmt) is working. next step is getting geometric and identifier languages into the framework. this involves a vocabulary for each, containing frequent words. we'll focus on identifying the first ten stars and explore what their vocabularies look like. 

initial vocabularies for ten stars are ready, with on the order of a thousand words, a bit more for geometry than for identifiers. images with less than six stars are being dropped, and turns out there are less than six stars in any of the images for starndx four. stars with fewer neighbors are harder to identify... this is something for later, more sophisticated, languages to handle.

*5.11.2017*

writing sentences in geometric and identifier languages. looks ready to move onwards. sentences have structure noun1 verb1 noun0, verb2 noun2. a subject-verb-object, verb-object pattern, with noun1 as the subject. noun1 is a triangle formed by the first three stars outward from image center. verb1 is distances from noun1 stars to noun0, the target star at image center, starndx three here. verb2 is distances from noun1 stars to noun2 stars, where noun2 is a triangle formed by the next three stars outward.

    'n:3:4:4 v:2:2:3 n:na, v:4:2:5 n:1:1:2', 'n:64:8854:8859 v:2:2:3 n:3, v:4:2:5 n:8808:8815:8834'
    'n:2:3:4 v:3:2:3 n:na, v:2:4:1 n:1:4:5', 'n:8815:8854:64 v:3:2:3 n:3, v:2:4:1 n:8834:8808:8859'
    'n:3:4:5 v:2:3:2 n:na, v:4:4:1 n:1:1:2', 'n:8854:64:8859 v:2:3:2 n:3, v:4:4:1 n:8808:8815:8834'
    'n:2:3:4 v:2:2:3 n:na, v:2:4:4 n:1:5:5', 'n:8808:8854:64 v:2:2:3 n:3, v:2:4:4 n:8815:8834:8859'

*4.11.2017*

initial languages are writing nouns. here's noun1 for a thousand images of star three. columns are geometric language, identifier language, and image count. clearly these nouns are sensitive to distance variations with yaw. we'll try living with it for now and move onwards.

    [('n:3:4:5, n:8854:64:8859', 318),
     ('n:1:3:4, n:8834:8854:64', 222),
     ('n:2:3:4, n:8815:8854:64', 178),
     ('n:3:4:4, n:64:8854:8859', 162),
     ('n:2:3:4, n:8808:8854:64', 109),
     ('n:3:4:5, n:8854:64:10', 11)]

*3.11.2017*

for writing nouns deterministically, stars can be ordered by distance from the image center. there's some ambiguity from variation of the distances with yaw because of pixelation. here's a section of starlist, showing starndx, row and column, x and y coordinates, and distance from the center. we'll start with noun1 representing the first three stars, and noun2 representing the fourth through sixth.

    [[64, 19, 11, -2.5, -5.5, 6.05],
     [8854, 17, 20, 6.5, -3.5, 7.39],
     [8859, 5, 10, -3.5, 8.5, 9.2],
     [8815, 13, 23, 9.5, 0.5, 9.52],
     [8808, 11, 23, 9.5, 2.5, 9.83],
     [8834, 16, 23, 9.5, -2.5, 9.83],

<img src="images/starndx3_nouns.png" align="center" width="240" height="240"/>

*1.11.2017*

implementing a python class languages_starimg focused on writing sentences about star images using various custom languages, lang1, lang2, lang3, lang4, etc. initial objective is to evolve a language pair, for example lang37 and lang51, that are effective at representing geometric structure and star identifiers on the encoder and decoder sides of neural machine translation.

*31.10.2017*

with info concerning image pixels and star identifiers available via libstarid image_info(target_starndx), next step is an initial iteration of our [two languages]((https://www.linkedin.com/pulse/small-deltas-from-neural-machine-translation-noah-smith/)), one reflecting geometric structures and relationships, the other reflecting star identifiers.

the focus is a quick proof of concept using neural machine translation to identify ten stars, starndxs zero to nine. the languages are to be as simple as possible for this first iteration. this means the nouns and their orderings, and so the sentences, are always similar for a particular star. sentences are generated from images in a deterministic manner that's not sensitive to image yaw. in a sense, first iteration sentences themselves are pretty simple star identifiers, setting aside flexibility and complexity for later iterations.

*30.10.2017*

with contemplation and reading over a two week vacation, there's an [overall picture](https://www.linkedin.com/pulse/small-deltas-from-neural-machine-translation-noah-smith/) of what star identification as neural machine translation looks like.

next step is to get the information needed for creating two languages available in python. this will come from the cpp stars app via libstarid and pybind11.

here's a quick memory refresh on the baseline sky. it's the 8876 stars brighter than visual magnitude 6.5. the skymap catalog rows for these stars are in the [skymap text file](https://raw.githubusercontent.com/noahhsmith/starid/master/stars/skymap.txt). we've now added a skymap ods spreadsheet with some basic parsing of the fixed width text file, so the hd, hr, and common name identifiers are easily accessible. for example starndx 3, used for many of the starid example images, is the fourth row. cg andromeda, hd 224801, hr 9080.

    SKY2000 J000043.63+451512.0	114	224801	53568	 BD+44	4538	9080	42458			CG    And 

there'll be something like an image_info(target_starndx) function in libstarid, returning an image info matrix for the target starndx. by default the image will have random yaw rotation. there'll be at least three columns. image matrix row, image matrix column, starndx. these are the pixels activated in the image. here's three rows of an info for starndx 3, showing starndxs 69, 91, and 97, and a plot of all pixels. last three columns are skymap number, ra degrees, dec degrees.

     [  4.00000000e+00   2.10000000e+01   6.90000000e+01   1.10134000e+05   2.99618791e+00   4.81523964e+01]
     [  2.00000000e+01   2.30000000e+01   9.10000000e+01   1.60054000e+05   4.08970500e+00   4.35950492e+01]
     [  5.00000000e+00   2.40000000e+01   9.70000000e+01   1.70028000e+05   4.28768208e+00   4.79474053e+01]
     
after a bit of experimenting, turns out [orion's too big](images/orion.svg) for our eight by eight degree field of view. at most, we can only see the belt together, mintaka, alnilam, and alnitak. it's worth noting this field of view was a default, to match standard ninties era star trackers. and it did in fact accidentally have some nice properties once we also defaulted to low resolution 28 by 28 pixel images to match the mnist dataset, resulting in 1000 arcsecond pixels. last two columns here are hd number and starndx.

    betelgeuse, alpha, 39801, 2062
    rigel, beta, 34085, 1719
    bellatrix, gamma, 35468, 1805
    mintaka, delta, 36486, 1861	
    alnilam, epsilon, 37128, 1909
    alnitak, zeta, 37742, 1952
    saiph, kappa, 38771, 2005

*12.10.2017*

on the encoder side, here's an example of generating symbols representing nouns, blue, and verbs, green. we can build symbols from numerical lengths. for a noun with sides 2.3, 5.1, 4.9 we could have the symbol 235149. on the decoder side, symbols are built from numerical starids.

![nouns and verbs](images/nouns and verbs.png)

*8.10.2017*

the more one thinks about it, the more attractive a star identification encoder decoder with an attentional interface approach grows. let's start sketching out some thoughts about the two halves.

on the encoder side, there's unsupervised clustering happening. it's giving us a sequence of phrases describing the star field that's the same regardless of rotation. this could be tougher than it sounds for low resolution images, as the pixelation means instability of relative positions and even the numbers of stars. a possibility is for the sequence of phrases to describe the star field in a radial sense, outward and inward, rather than a rastering or rotational sense.

on the decoder side, there's a sequence of translations happening. the encoder maps a variable length source sequence to a fixed length vector, and the decoder maps the vector back to a variable length target sequence, with the attentional interface augmenting the fixed length vector between. they're trained to give the correct target sequence for a source sequence.

we change an image recognition problem into a translation problem. given a sequence of phrases representing a star field, translate it into a sequence of star identifications.

*29.9.2017*

here's a curious thought. when a person identifies stars, it can have a verbal, sentence-like sequential nature. there's orions belt, and up there's his upraised arm, and there's betelgeuse, and then down there's his legs, etc. this has similarities to the attention giving decoder rnn in machine translation and image captioning.

*24.9.2017*

after a few iterations, reached some enlightenment from the montreal papers about the core concept of attention. it's about something giving attention to something else. it has a fundamentally dual nature. it's sequential. the something giving attention is an rnn. basically, we either have an rnn giving attention to another rnn, or an rnn giving attention to a cnn. note a google paper from earlier this year dispenses with rnns and cnns, leaving pure attention. they refer to it as self attention, implying something giving attention to itself.

*17.9.2017*

studying two recent papers, one about visual attention and the other about time series prediction, seemingly separate topics, here's a curious fact. both involve encoder-decoder dual rnns. it seems this will be the focus in the coming months, for both star identification and time series.

*10.9.2017*

interesting paper about [time series uncertainties and bnns](https://eng.uber.com/neural-networks-uncertainty-estimation/). this could be directly applicable to the kpi modeling project at work, and a separate direction going forward. pure times series stuff is a topic with little obvious relation to star identification... 

*1.9.2017*

papers from around 2014-2015 concerning attention have a control systems perspective, which hasn't been so noticeable in pure cnn and rnn papers. this may just be reflecting the fact that reinforcement, task based, non differentiable learning are involved. different communities and priorities. in any case, it's welcome, and strengthens the picture that has been developing of parallel developments in aerospace and computer science from the beginning of the space age.

*20.8.2017*

from here, i may occasionally [post on linkedin](https://www.linkedin.com/pulse/machine-learning-attention-star-identification-noah-smith).

*20.6.2017*

a nice machine learning project at work has been taking up a lot of time, but it's not a bad time for a pause. with both triangles and rnn working well, the next focus may be convents and incorporating batch normalization.

*4.6.2017*

unwrapping sequences is a breakthrough for learning with a recurrent network. here are results for training a gru cell. seconds, batch, loss, accuracy with two hundred states
 
    5819.3, 9700, 4.53, 0.43

three hundred states

    9089.9, 9800, 3.72, 0.62
    
four hundred states

    10674.1, 7500, 3.27, 0.75
    
a slow, noisy, overheating, six year old laptop learning to recognize a thousand stars. r2017c released.

*28.5.2017*

it's turning out that random input sequence phase offsets are a challenge for recurrent networks. it's usually assumed one knows where the sequences begin, whereas here they're circular wrapped. since they're one dimensional, it's fairly straightforward to introduce deterministic unwrapping.

*23.5.2017*

for a thousand stars, rnn and cnn train slowly. the sequential, recurrent approach should be easier to speed up, as it's less sensitive to image yaw. to make training practical on a six year old laptop, the focus will be on improved rnn design.

*21.5.2017*

for identifying one hundred stars, both rnn and cnn are getting better than ninety percent accuracy for roughly ten minutes of training, so we're quickly jumping to a thousand stars. this is clearly much more of a challenge. accuracy increases from 0.001 to about 0.005 for fifteen minutes of training

*13.5.2017*

introducing regularization so the networks build simpler models, reflecting more common patterns. picturing the network as a set of weight vectors, regularization prefers smaller weights. weight decay and dropout implemented. 

*6.5.2017*

increased the number of stars identified by rnn and cnn beyond ten for the first time. first increase was to one hundred stars. training is slower but still very reasonable on a six year old laptop. the path seems clear to push towards all 8876 stars. r2017b released.

*5.5.2017*

recurrent and convolutional networks now working in parallel on top of libstarid.

*30.4.2017*

convnet using runtime images from libstarid is working. code is much cleaner without all the filesystem stuff.

*27.4.2017*

star image and inverse now working, with direct cpp eigen and python numpy using pybind11.

    image = libstarid.image(starndx=13)
    starndx = libstarid.id(image)
    plt.matshow(-1 * image, cmap='Greys', interpolation='nearest')
    plt.show()

![image](images/image.png)

*14.4.2017*

underlying cpp classes are refactored and updated in preparation for the tensorflow op. they're ready to output eigen matrices representing star images directly into tensorflow graphs. the switch from armadillo to eigen is complete. 

here's an example of creating an image of star number 13, with random image yaw, then identifying it from the image.

    image_matrix imgmat = new_image_matrix(13, sky);
    star_identifier ider(imgmat, pairs);
    int result = ider.id();


*11.4.2017*

slim down bits in sky binary file from naive initial 1.8 mb. first iteration reduced size to 0.7 mb.

*3.4.2017*

skeleton of star images tensorflow op is working. current concept is that on startup it will load the sky binary file as input, then for each graph iteration output a 28 x 28 x n tensor of star images, with a label tensor.

*31.3.2017*

next step is to increase the number of stars the convnet can identify to 100, then 1000, then 8876. this means much larger amounts of training data.

begin work on a tensorflow op and cpp kernel to dynamically generate star images in memory at runtime. there's no need to use the filesystem during training. this is a good thing since image files for training 8876 stars would be big and slow. we'll generate them on the fly as fast as possible. it's also nice to be able to easily switch subsets of the stars, for example just the first hundred or first thousand.

*26.3.2017*

r2017a. both lb convnet and rb triangles working on the same mnist style star images. first run results, before any performance work

              ok      t
    -----  -----  -----
       lb  0.897  0.173
       rb  1.000  5.494
       
convnet can identify ten stars, triangles can identify all stars, or at least for now, all 8876 brighter than 6.5.

*25.3.2017*

basic triangles method is complete. the following is for a typical image. we're identifying the star at the center and there are 8876 possibilities. there are thirty other stars and for each an attempt is made to discard incorrect ids. in each attempt, the ideal is that the possible ids drop quickly to one. here are results using the most naive approach. in one attempt possible ids drop to ninety.

<img src="images/ab1.png"/>

next to most naive approach. an adjustment to extract more information from the image. many attempts are now dropping to twenty or less possibilities, several to five.

<img src="images/ab2.png"/> 

another adjustment.

<img src="images/ab3.png"/> 

final adjustment.

<img src="images/ab4.png"/> 

*6.3.2017*

next two weeks will pretty much be about vacation, so time for a bit of planning. r2017a with parallel image input into lb and rb is first. this heads towards a cpp kernel for dynamically generating images within tensorflow.

*5.3.2017*

triangle based identification is now working for mnist style images. this was really a challenge. [here's](images/itworks.png) an image of the eureka moment. nice convergence over nineteen triangles.

*27.2.2017*

triangle processing is now doing a decent job of handling deep cycles and iterations - tracing star pairs down through multiple layers of linked triangles. what this is revealing is just how tough the problem is for low angular resolution mnist style images. at such low resolution each star triangle contains a relatively small amount of information, or inversely a relatively large amount of uncertainty. to gather enough information to identify a star, you need a lot of low res triangles.

the focus now seems headed towards directly using higher level geometrical structures containing more information, despite the low resolution of the lower levels. these structures can be built out of triangles. it also may be possible to dynamically trace through rather arbitrary geometries. maybe graphs of stars is a useful way of expressing this. or star networks...

*20.2.2017*

now that it's easy to see exactly when and where the correct star is lost, it makes sense for development purposes to be able to pass its id all the way down in the code. things get much more deterministic.

and the beginnings of how it came about are creeping forward [here](http://starid.org/about).

*17.2.2017*

increased the maximum star pair angle from four degrees to eleven degrees so that any star pair in the field of view is available. this increases the number of star pairs across the sky to 751k.

*16.2.2017*

for 8876 stars brighter than 6.5 and position quantization uncertainty around a thousand arcseconds, in a typical triangle there are roughly 30k paths around the loop - three stars forming three linked pairs around the sides.

*14.2.2017*

interesting machine learning review [here](https://blog.ought.com/nips-2016-875bb8fadb8c#.5bk6rnm81)

*13.2.2017*

after a weekend of experimentation, the method for reducing the number of candidate pairs that's showing the most promise uses a loop of three stars forming three linked pairs around three triangle sides. it's made practical by using hash maps everywhere. performance clearly could be an important question with tens of thousands of pairs...

*6.2.2017*

with stars brighter than 6.5 and pairs up to four degrees, triangle sides begin with tens of thousands of candidate pairs. with loose contraints because of position quantization, there are a lot of false positives in such a large number of candidates. multiple triangles are needed to improve the constraints. the following sketches some important components.

 ![triangle](images/triangleb.jpg)

*30.1.2017*

source code comments beginning with /// and ### are now extracted into markdown available [here](comments.md). the python app performing this is a new project [here](https://github.com/noahhsmith/commenter).

*23.1.2017*

the point in this discussion of uncertainty and triangle methods - with mnist style images a rules based approach becomes harder. previously the image was from a spacecraft grade star tracker. now it's from a childrens toy. it's a useful challenge...

*22.1.2017*

with mnist style images and a four degree radius field of view, a pixel is roughly

    >> ((4*pi/180)*648e3/pi)/14
    ans =  1028.6

arcseconds. the position uncertainty of a star is half this, and triangle side tolerance should be on this order of magnitude. early stopping methods are needed to reduce the number of pairs and stars in triangle processing.

*20.1.2017*

triangle logic

![triangle](images/triangle.jpg)

*19.1.2017*

concepts for image and triangle

![concepts](images/concepts.jpg)

*16.1.2017*

mnist viewer. a bit of python code in data/mnist_viewer to see what's in the mnist style data files. this is bare minimum functionality for now. two examples for star 4. these demonstrate axjndx axindx plane. variations of relative positions because of quantization are clear - relative positions vibrate as yaw varies, creating inherent uncertainties in the mnist images...

![imgndx3](images/star4a.png)![imgndx13](images/star4b.png)

*15.1.2017*

new school images are now in mnist and tfrecords files, and learning is working. using the first ten skymap stars and a few minutes of training

    /usr/bin/python3.5 /home/noah/dev/starid/learning-based/predict.py
    0.778 correct

almost 0.8 correct - this is a significant improvement and reason to suspect there was subtle bug in the old school mnist file - possibly a duplication of images that limited learning.

*14.1.2017*

concept for image class. an image is a group of unit vectors clustered around the z axis. there is always a center star with unit vector 0, 0, 1 - this can be implicit - an image is always of a star. the explicit unit vectors are the nearby stars that happen to be in the image.

when you talk about a star - say starndx 3 - you can can just as well talk about the image of star 3, with star 3 as its 0, 0, 1 axis.

*7.1.2017*

more automation with the the mnist style dataset

    /usr/bin/python3.5 /home/noah/dev/starid/system.py

for n=100, percent ok and time in seconds
lb, 0.5, 0.548
rb, 0.9, 0.334

*5.1.2017*

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

*4.1.2017*

cereal and optionparser. with initial functionality in place, it's time for a round of refactoring and performance. two cpp header-only libraries have jumped in and they're giving a pretty good feeling about the state of modern cpp.

cereal has quickly allowed two classes, representing the complete sky and all star pairs, to be streamed to and from disk. this is an order of magnitude improvement over runtime generation - say from six seconds to half a second on a six year old laptop. optionparser has taken some pain out of command line handling.

*3.1.2017*

names matter. cpp caused some unnecessary pain last night - working on serializing the pairs over whole sky object, things were going smoothly

    #include <cereal/types/string.hpp> for strings
    #include <cereal/types/tuple.hpp> for tuples
    #include <cereal/types/vector.hpp> for vectors
    #include <cereal/types/unordered_map.hpp> for unordered maps
    #include <cereal/types/pair.hpp> for pairs... right?

wrong.

    #include <cereal/types/utility.hpp> for pairs

and it's not cereals fault. cpp puts std::pair in utility.

*29.12.2016*

r2016c new release on github. system is working - rules-based and learning-based subsystems are functioning

    /usr/bin/python3.5 /home/noah/dev/starid/system.py
    true identity 1600
    learning-based identification 1600
    rules-based identification 1600

lb is using convnet in tensorflow. rb is using triangles in cpp.

*27.12.2016*

initial convnet predictions as part of establishing an overall system for parallel evolution of triangles and convnet, there was a first convnet evaluation run this morning. everything was mnist-style except using randomly yawed images of ten stars.

convnet identifications were right for 0.6 of the evaluation examples. pretty impressive for five minutes of naive training on a six year old laptop. and plenty of room for improvement.

*26.12.2016*

data formats. after some interesting experiences today, my picture is that tfrecords is natural within tensorflow, but with just numpy the mnist format is nice. this means keeping both types of files side by side for a given data set. tensorflow training with tfrecords, and numpy manipulation with mnist...

*24.12.2016*

complete baseline data on github. in preparation for creating a project level frontend for triangles cpp and infer tensorflow - all the baseline data files are now in the git repo.

ideally the frontend will quickly have an end to end demo acting as a system level test.

*22.12.2016*

ten star subset of skymap catalog with brightness cutoff at mv 6.5 skymap gives

    stars 8876, dim stars 290585, error_stars 0.

ten of these 8876 are used for testing

    starndxs 800, 1600, 3200, ... 8000.

there's now a subset of the skymap catalog for faster initialization, containing just these ten. when using this subset - star 800 becomes star 0, star 1600 becomes star 1, ... star 8000 becomes star 9. also added a subset for the 8876 stars.

*18.12.2016*

r2016b. everything is working again in stars, triangles, and infer.

next step seems to be an evaluation framework for simultaneous development of triangles and infer - heuristic and machine learning approaches...

*17.12.2016*

float int table class. this returns to a discussion of the very specific type of algorithm and data structure used repeatedly in star id - a type of lookup table, bordering on a hash table.

there is a sorted vector of floats representing a physical quantity. each float has an associated int identifying a star. this a two column float and int table. the common usage is to search for all of the floats within a given range, from lower float to upper float.

representing this as it own class, there is plenty of room for search optimization. mortari's k-vector method for example takes this in a direction toward a hash table, with the indexes of lower float and upper float computed by equation.

*7.8.2016*

deconvnet. before experimenting with convnet models, a deconvnet could be implemented for insights into star pattern learning. this fits with the concept of impulse signals to understand convnet response, and heads in the direction of inverse problems.

*5.8.2016*

star pattern impulse signal. for randomly yawed 28 by 28 images of a star pattern, is there a pattern that could act as an impulse signal with a clean and understandable convnet response. it's likely either a star pair or triangle. the star separations are a critical factor, relating to local versus global features, filters, pooling, etc. maybe a right triangle with ratios 1 : 2 : sqrt(5) is a useful probe signal.

*28.7.2016*

starid data v1 available. baseline input data is here, starid_data_v1.tar.gz. every image has been randomly yawed, so the mnist stuff is non standard. *a.* files are 60k training images, *b.* files are 10k test images.

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

*27.7.2016*

yawed starid is working. yawed and unyawed versions of starid and mnist are working, so the input layer is essentially taken care of now and the focus changes to learning. an interesting possibility is packaging the data and code of the input layer in a standalone way for broader usability.

*23.7.2016*

yawed mnist is working. it finds non zero pixels and rotates their coordinates. there is a bit of aliasing for some rotation angles due to rounding of coordinates, but the result is essentially as expected - rotated mnist numerals. now to feed star patterns through the same processing.

*17.7.2016*

yawed mnis.
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

*16.7.2016*

mnist format. with code from eric yuan, mnist files are reading into cpp armadillo matrices. after adding code for writing back to mnist files, experiments can begin with both yawed mnist and star patterns. for identifying ten stars, any mnist pipeline should work. it would be nice to write directly to tfrecords files from cpp as well, but the python mnist to tfrecords converter is fine for now.

*9.7.2016*

throughput. with tensorflow a focus becomes throughput - for an arbitrary number of machines, cpus, and gpus - provide information at a rate that keeps everything busy over arbitrarily long runs. this is practical for starid. what's needed is a fast example generator.

the concept is to bypass the file system and directly feed in examples over the entire sky, random pointing and yaw, any limiting magnitude and field of view size, etc.

*3.7.2016*

big picture update. star model

    l0 - hardware star sensor measurements
    l1 - star pointing vectors in a sensor coordinate frame
    l2 - star patterns

heuristic starid

    pairs - l1 star pair angle matching
    starid learning
    svm - support vector machines
    convnet - convolutional networks

l2 star patterns and mnist. 10x10 and 100x100 star pattern grids are reasonable to experiment with. 10x10 is too small and 100x100 is too large. a choice between is too arbitrary. tensorflow makes it simple to work with conv nets and the mnist 28x28 dataset. so 28x28 it is. star patterns should fit into mnist tf models. an interesting path will be seeing how they handle arbitrarily rotated mnist images, equivalent to the yaw problem.

*2.7.2016*

global templates and local features. here's some interesting terminology from a 2004 image recognition paper. svm is about matching a global template. conv net is about matching local features. invariant features, such as a star pattern, are somewhere between or above the global template local feature axis.

*27.6.2016*

the yaw problem. say you're given a set of star vectors in the sensor coordinate frame and asked to identify one near the yaw axis. the other vectors are features, are a function of yaw, and at the same time represent an invariant pattern that can be learned.

old school is to normalize away yaw. this is error prone.

new school is to recognize the pattern regardless of yaw. convnet svm combinations should be capable of this.

*22.6.2016*

optimization. svm is about finding the minimum of alpha K alpha. its quadratic so there is one minimum. the concern is that K is a dense matrix that gets big with training set size.

old school is divide and conquer using smo for a sequence of simple-as-possible sub problems.

new school is using tensorflow for brute force with modern hardware - gpu, tpu, etc.

*21.6.2016*

svm classes. tensorflow jargon is nice and can be adopted here. two high level concepts are a model, and training a model. a model makes predictions and with training its predictions become better.

the two core svm classes are model and train. the pure cpp implemetation will focus on these two classes. the tensorflow implementation can try to use the model class and reimplement train as a tensorflow graph - possibly with a new cpp tf kernel.

*11.6.2016*

tensorflow. with svm well underway, interesting to note at this point that it looks like the next approach should be tensorflow. the name was new eight months ago. now it seems to be the natural lost-in-space tool - next generation matrix operations.

*11.6.2016*

svm train. the concept is to implement svm in parallel with libsvm using armadillo and modern cpp. the libsvm standard heart scale dataset can validate the new implementation. starting point is an svm train class.

hmmm, on closer examination, the heart scale data is riddled with null values, reflected in unusual formatting. null handling is a detour, so the heart scale dataset is out for now.

*7.6.2016*

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

*4.6.2016*

sequential minimal optimization. looks like the focus for the initial svm implementation will be smo. for an aerospace person the svm focus on quadratic programming is as comfortable as home. the histories of kalman filtering and kernel machines could be an interesting topic to explore.

training examples and false stars. false stars are mostly about making interesting training examples for svm and ann development. with modern sensors they are rare in l2. they make learning much more interesting though, so we will increase their frequency. this could also be viewed as increasing robustness for lower performance and less expensive sensors.

for real sensors, false stars are a consideration, particularly in l0. the classical problem for spacecraft star trackers is cosmic rays hitting the detector and dust or debris in front of the optics. these are time varying. wait long enough and they go away. normally they are handled by the processing from l0 to l1.

but we can also imagine a phone camera pointed at the night sky. to go from l0 to l1, we have to pick the true stars out of the images.

*3.6.2016*

l1a is ideal pointing vectors in the sensor frame, parameterized by

    fov - field of view radius in arcseconds
    mv - faintest star visual magnitude

l1b is more realistic pointing vectors in the sensor frame, adding the parameters

    noise - pointing vector noise equivalent angle in arcseconds
    false stars - gaussian distribution of false star counts

*29.5.2016*

l1a and l1b. as part of creating training examples, modelling sensor noise and errors becomes more important. this is reflected in l1b.

    l1a is ideal three dimensional star pointing vectors in the sensor frame.
    l1b adds pointing noise and false stars.

*28.5.2016*

feature vector tradeoff. for generating training sets, it's good to clarify that the feature vector is based on knowing, for a given star and sensor, the nearest observable neighbor. this allows the feature vector to be independent of yaw.

this is fine for l1 and l2. l0 is complicated by variable sensitivity.

*16.5.2016*

training class in base. fundamental concepts currently represented in the base build are catalog, sensor, and pointing. with parallel training of knn, svm, and ann beginning, it becomes a fourth fundamental concept.

svm kernel selection. to begin with the minimal svm kernel, simple dot products between feature vectors, should be sufficient. a nonlinear kernel example would be useful for comparison. possibly a gaussian kernel. it also seems likely there will not be performance problems using a batch mode implementation with n = 100 inputs. possibly an on-line implementation should follow.

*14.5.2016*

number of ann hidden neurons. the current picture is to try an n = 100 feature vector as input, representing a ten by ten grid pattern. the number of outputs is one, binary classification.

for ann a rough guide is that for m outputs and n inputs, the hidden layer can have about sqrt(mn) = 10 neurons. this give a network with a nice 100 - 10 - 1 structure. on the other hand, the idea is to start with as few hidden neurons as possible. start with what is known to be too few, and increase their number only as needed. this suggests a 100 - 5 - 1 or 100 - 2 - 1 structure to start with.

*13.5.2016*

simple knn working. end to end knn unit test added, now turning to svm and ann.

*11.5.2016*

simple approach for knn. for a given feature vector, the nearest neighbors have the largest dot products. all dot products are from zero to one here since the feature vector components are positive or zero. the simple approach is k = 1 and the input feature vector is classified with the training feature vector having the largest dot product.

*8.5.2016*

    l0 - unprocessed sensor measurements
    l1 - pointing vectors in sensor frames and the celestial frame
    l2 - feature vectors

    ptq - pointing vector classification using star pair angular separations
    knn - feature vector classification using k nearest neighbors
    svm - feature vector classification using support vector machines
    ann - feature vector classification using artificial neural networks

current emphasis is on vectorized processing using blas. concurrency can follow.

*5.5.2016*

feature vector size. first questions for knn seem to be feature vector size. for

    case a - 10 by 10 grid so 100 features
    case b - 100 by 100 grid so 10000 features

is case a good enough for distinguishing 8876 stars brighter than mv 6.5? is case b practical performance-wise?

histograms of feature counts for 8876 feature vectors. bins are 0-5, 5-10, 10-15, etc.

    case a - 104 4081 3192 1142 297 58  2  0  0 0
    case b - 92  3565 3129 1365 407 190 91 30 5 2

histograms of dot products between 8876 normalized feature vectors. bins are 0-0.1, 0.1-0.2, 0.2-0.3, etc.

    a - 6712609  14730674 12653854 4543313 694507 49639 2523 114 11 4
    b - 30004395 9117682  258869   5973    317    9     2    1   1  0

case b feature vectors are more distinct, as expected.

*1.5.2016*

levels 0, 1, 2. sensor data abstracts nicely as

    level 0 - unprocessed measurements, hardware level
    level 1 - pointing vectors
    level 2 - feature vectors

we're interested in levels 1 and 2. mostly level 2...

*27.4.2016*

feature vectors. it makes sense to add feature vectors to the base as part of sensor obs. a feature vector can represent a grid over observation tangent plane coordinates. an n by n grid of zeros and ones means an n^2 feature vector and feature space.

there's a tradeoff between resolution and dimensionality. for a four degree radius and magnitude limit around seven, so maybe 10 to 50 stars in the field of view, n = 10 or 100 seem possible...

*24.4.2016*

pairs and triads are working. pairs based triad identification is working. now to include quads for validation. serious thinking began yesterday for machine learning builds in patterns and neuralnets. one concept is a grid pattern representing the sky around a given star. a rule makes the grid independent of yaw. in physical terms this is about defining tangent planes on the sky. use the nearest neighbor star, the nearest bright star, etc.

*23.4.2016*

tolerance for triads. things are simpler if the candidate sets id(ab), id(ac), id(bc) do not overlap. this is true if the angles ab, ac, and bc are sufficiently different. the current criteria is that they differ by an arcminute or more.

*20.4.2016*

pairs triplets quadruplets concept. given three unit vectors a, b, c and a function id() that returns a list of candidate ids...

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

*18.4.2016*

triplets class. given an observation of n stars, what sequence of pairs or triplets best leads to a pairs based identification? mortari addresses this in his 2004 paper with a sequence of triplets that jump around the field of view, making a breadth first search rather than a depth first search. this can be represented as a triplets class. given n stars it returns a breadth first sequence of triplets.

*16.4.2016*

pairs method. ready to implement pairs based method. common terminology includes triangles for three stars, pyramids for four stars. a build for pairs is added alongside the builds for base and gtest. placeholder builds for patterns and neuralnets are also added.

*14.4.2016*

sensor class ready. onward to the first star identification implementation...

*9.4.2016*

sensor class and obs struct. sensor class now has a pointing vector and yaw constructor, a member attitude, and support for rotation vectors, rotation matrices, and quaternions. for observed stars, return an obs struct with both ideal values and measurement errors.

*5.4.2016*

sensor class, geometry, cpp linear algebra library. a sensor class means multiple reference frames, rotations, and representations of unit vectors, so a linear algebra library becomes necessary here. i've mostly used armadillo and a bit of eigen and gnu scientific library. time for a quick review of the field.

just glancing at the wikipedia page for linear algebra libraries, eigen and armadillo are the choices. the matlab orientation of armadillo decides it - continue with armadillo.

*3.4.2016*

sensor class. now that the sky is in place, time to create a sensor. sensor class is based on the pinhole camera model. first-order characteristics are attitude, sensitivity, and field-of-view.

unit vectors are the representation for stars. unit vector point on the sky and a yaw rotation are a useful representation for attitude here, particularly in the constructor, and are reinterpreted as a rotation matrix or quaternion as needed.

tangent plane coordinates are the representation for field-of-view. uncertainties will be modeled in the observation class. the sensor class models only the ideal truth.

*2.4.2016*

star pairs class first results. star pairs class is now working and first results for mv = 6.5 and radius = 4 degrees are

    bright stars 8876 dim stars 290585
    atable size 56585 med 2.79 max 3.99

so for ~9k bright stars there are ~56k neighbor pairs, and the pair separations in degrees have median 2.8 and max 4

*31.3.2016*

star pairs class. the star pairs class can be based on the concept of a star and its neighbors, applied sequentially to each of the significant stars in the catalog... star pairs for the entire sky can be collected from these star objects into a main vector. as pairs stream towards the main vector, duplicates can be removed using a hash table with a key string composed from both pair members.

*28.3.2016*

stars near some point on the sky is working. results from asking what is near a point near cassiopeia, with a mag 6.5 cutoff

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

*26.3.2016*

stars near some point on the sky. a function for the catalog class, the algorithm i've used for years came from a mortari paper. it uses lookup tables for the x, y, and z axes to create three rings or bands on the sky. here's some ring search matlab

*25.3.2016*

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

*24.3.2016*

star pairs class and angle lookup. star pair angle lookup seems to be the clearest terminology for what is needed to search the star catalog. early objectives are a skymap star catalog class and a star pair class with angle lookup

*20.3.2016*

catalog class and skymap records. a skymap record is 523 bytes long, including two control bytes at the end. this matlab code picks out certain useful values. more are available as shown in the skymap specification.

*18.3.2016*

a nice statement of the problem. mortari 2004

> The star polygon geometric structure is defined by the set of M = n! / (n − 2)! 2! interstar angles associated with a spherical polygon set of n stars, such as pairs (n = 2), triangles (n = 3), as well as pyramids (n = 4). The spherical polygon is closely related to the usual polygon, where the straight line sides are replaced by great circle arcs (angles) on the surface of a unit sphere connecting the neighboring pairs of stars in a set of p stars. More specifically, the star pattern geometric structure for the purpose of star identification is defined by the set of M interstar angles {ϑij = ϑji = cos−1 (b T i bj )} measured between each distinct pair of the p lineof-sight vectors {(bi , bj ) : (i, j) ∈ {1, 2, . . . p}} that point from the sensor toward the vertices of the star spherical polygon on the celestial sphere. Note we adopt the convention that the measured line-of-sight unit vectors with components in the sensor body axes are denoted bi , whereas the corresponding line of sight vectors based on cataloged information with components in the inertial reference frame of the star catalog are denoted rI . The whole objective of star identification can be boiled down to finding the correspondence between indices (i) of measured stars and the indices (I) of cataloged stars.

*16.3.2016*

skymap catalog binary text file. a curious thing about the skymap catalog - it is a type of binary text file. each line contains a specified number of bytes per field, and each field has a type (int, string, etc). it's strongly-typed. it's exact memory layout is defined. it could be equated to serialized objects of a cpp class. probably the quicker approach for initial implementation is to view it just from a string handling perspective, but a later deserialization approach would be interesting.
