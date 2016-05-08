# starid
http://staridentification.blogspot.com

related files - https://goo.gl/xgjpmb

the lost-in-space problem is divided here into three levels - l0, l1, l2

l0 - unprocessed measurements, hardware dependent

l1 - three dimensional unit vectors representing stars in sensor and celestial frames
    - ptq - angles between unit vectors

l2 - high dimensional feature vectors representing star patterns
    - knn - similarity of feature vectors
    - svm - linear and nonlinear kernel separation of feature vectors
    - mlp - nonlinear response to feature vectors

the emphasis here is on vectorized processing of feature vectors
