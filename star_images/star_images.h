#ifndef STAR_IMAGES_H
#define STAR_IMAGES_H

#include "/home/noah/tf/lib/python3.5/site-packages/tensorflow/include/tensorflow/core/framework/op.h"
#include "/home/noah/tf/lib/python3.5/site-packages/tensorflow/include/tensorflow/core/framework/shape_inference.h"
#include "/home/noah/tf/lib/python3.5/site-packages/tensorflow/include/tensorflow/core/framework/op_kernel.h"

using namespace tensorflow;

REGISTER_OP("StarImages")
    .Input("to_zero: int32")
    .Output("zeroed: int32")
    .SetShapeFn([](::tensorflow::shape_inference::InferenceContext* c) {
      c->set_output(0, c->input(0));
      return Status::OK();
    });

class StarImagesOp : public OpKernel {

 public:

  explicit StarImagesOp(OpKernelConstruction* context) : OpKernel(context) {}

  void Compute(OpKernelContext* context) override;

};

REGISTER_KERNEL_BUILDER(Name("StarImages").Device(DEVICE_CPU), StarImagesOp)

#endif
