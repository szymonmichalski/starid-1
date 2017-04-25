#include "libimgop.h"

void imgop::Compute(OpKernelContext* context) {
  const Tensor& input_tensor = context->input(0);
  auto input = input_tensor.flat<int32>();

  Tensor* output_tensor = nullptr;
  OP_REQUIRES_OK(context, context->allocate_output(0, input_tensor.shape(), &output_tensor));
  auto output = output_tensor->flat<int32>();

  int starndx = 4;
  stars::image_matrix imgmat = stars::pointing_vectors::new_image_matrix(starndx, sky);

  const int ndxn = input.size();
  for (int i = 0; i < ndxn; i++) {
      if (imgmat(i) > 0) output(i) = 1;
  }

}
