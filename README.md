# starid
http://staridentification.blogspot.com and related files https://goo.gl/xgjpmb

three levels

l0 - unprocessed measurements, hardware dependent

l1 - three dimensional pointing vectors in sensor frames and celestial frame

l2 - higher dimensional feature vectors

approaches

ptq - angles between pointing vectors

knn - similarity of feature vectors

svm - linear and kernel separation of feature vectors

mlp - nonlinear response to feature vectors

current emphasis is on simd processing using blas and lapack. concurrency will follow.
