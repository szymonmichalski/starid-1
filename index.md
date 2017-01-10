07.01.2017

more automation
with the the mnist style dataset

/usr/bin/python3.5 /home/noah/dev/starid/system.py
n 100     ok      t
   lb  0.500  0.548
   rb  0.900  0.334


05.01.2017

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

04.01.2017

cereal and optionparser
with initial functionality in place, it's time for a round of refactoring
and performance. two cpp header-only libraries have jumped in and they're
giving a pretty good feeling about the state of modern cpp.

cereal has quickly allowed two classes, representing the complete
sky and all star pairs, to be streamed to and from disk. this is an order
of magnitude improvement over runtime generation - say
from six seconds to half a second on a six year old laptop. optionparser
has taken some pain out of command line handling.

http://optionparser.sourceforge.net/

https://github.com/USCiLab/cereal

03.01.2017

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


29.12.2016

r2016c
new release on github
system working
rules-based and learning-based subsystems are functioning

/usr/bin/python3.5 /home/noah/dev/starid/system.py
true identity 1600
learning-based identification 1600
rules-based identification 1600

lb is using convnet in tensorflow. rb is using triangles in cpp.


27.12.2016

initial convnet predictions as part of establishing an overall system for parallel evolution of triangles and convnet, there was a first convnet evaluation run this morning. everything was mnist-style except using randomly yawed images of ten stars.

convnet identifications were right for 0.6 of the evaluation examples. pretty impressive for five minutes of naive training on a six year old laptop. and plenty of room for improvement.
