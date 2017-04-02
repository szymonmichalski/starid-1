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

  void Compute(OpKernelContext* context) override {
    // Grab the input tensor
    const Tensor& input_tensor = context->input(0);
    auto input = input_tensor.flat<int32>();

    // Create an output tensor
    Tensor* output_tensor = NULL;
    OP_REQUIRES_OK(context, context->allocate_output(0, input_tensor.shape(),
                                                     &output_tensor));
    auto output = output_tensor->flat<int32>();

    // Set all but the first element of the output tensor to 0.
    const int N = input.size();
    for (int i = 1; i < N; i++) {
      output(i) = 0;
    }

    // Preserve the first input value if possible.
    if (N > 0) output(0) = input(0);
  }
};

REGISTER_KERNEL_BUILDER(Name("StarImages").Device(DEVICE_CPU), StarImagesOp);

//class star_images_op : public OpKernel
//{

//public:
//    star_images_op();
//};

#endif
