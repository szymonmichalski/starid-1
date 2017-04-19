#include "imgop.h"

void imgop::Compute(OpKernelContext* context)
{
  // Grab the input tensor
  const Tensor& input_tensor = context->input(0);
  auto input = input_tensor.flat<int32>();

  // Create an output tensor
  Tensor* output_tensor = NULL;
  OP_REQUIRES_OK(context, context->allocate_output(0, input_tensor.shape(), &output_tensor));
  auto output = output_tensor->flat<int32>();

  // Set all but the first element of the output tensor to 0.
  const int N = input.size();
  for (int i = 1; i < N; i++) {
    output(i) = 0;
  }

  std::string datadir = "/home/noah/starid/stars/data/";
  stars::Sky sky;
  std::ifstream is1(std::string(datadir + "sky"));
  cereal::BinaryInputArchive iarchive1(is1);
  iarchive1(sky);

  // Preserve the first input value if possible.
  if (N > 0) output(0) = input(0);

}
