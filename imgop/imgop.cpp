#include "imgop.h"

void imgop::Compute(OpKernelContext* context)
{
  const Tensor& input_tensor = context->input(0);
  auto input = input_tensor.flat<int32>();


  std::string datadir = "/home/noah/starid/stars/data/";
  stars::Sky sky;
  std::ifstream is1(std::string(datadir + "sky"));
  cereal::BinaryInputArchive iarchive1(is1);
  iarchive1(sky);


  Tensor* output_tensor = NULL;
  OP_REQUIRES_OK(context, context->allocate_output(0, input_tensor.shape(), &output_tensor));
  auto output = output_tensor->flat<int32>();
  const int ndxn = input.size();
  for (int i = 1; i < ndxn; i++) output(i) = 0;
  if (ndxn > 0) output(0) = input(0);
}
