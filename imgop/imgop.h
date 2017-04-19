#ifndef STAR_IMAGES_H
#define STAR_IMAGES_H

#include "/home/noah/tf/lib/python3.5/site-packages/tensorflow/include/tensorflow/core/framework/op.h"
#include "/home/noah/tf/lib/python3.5/site-packages/tensorflow/include/tensorflow/core/framework/shape_inference.h"
#include "/home/noah/tf/lib/python3.5/site-packages/tensorflow/include/tensorflow/core/framework/op_kernel.h"

#include "sky.h"
#include "pointing_vectors.h"
#include "cereal/archives/binary.hpp"

using namespace tensorflow;

REGISTER_OP("StarImagesAndLabels")
    .Input("to_zero: int32")
    .Output("zeroed: int32")
    .SetShapeFn([](::tensorflow::shape_inference::InferenceContext* c) {
      c->set_output(0, c->input(0));
      return Status::OK();
    });

class imgop : public OpKernel {

 public:

  explicit imgop(OpKernelConstruction* context) : OpKernel(context) {}

  void Compute(OpKernelContext* context) override;

};

REGISTER_KERNEL_BUILDER(Name("StarImagesAndLabels").Device(DEVICE_CPU), imgop)

#endif
