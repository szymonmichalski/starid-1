# starid
http://staridentification.blogspot.com and related files https://goo.gl/xgjpmb

three levels of the lost-in-space problem

l0 - unprocessed measurements, hardware dependent

l1 - three dimensional pointing vectors representing stars in sensor and celestial frames

l2 - high dimensional feature vectors representing star patterns

approaches

ptq - angles between pointing vectors

knn - similarity of feature vectors

svm - linear and kernel separation of feature vectors

mlp - nonlinear response to feature vectors

the emphasis is on simd processing using blas, lapack, etc
