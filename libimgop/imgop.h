/// *imgop*
///
/// tensorflow op generating runtime star images and labels.
///

#ifndef STAR_IMAGES_H
#define STAR_IMAGES_H

#include "/home/noah/tf/lib/python3.5/site-packages/tensorflow/include/tensorflow/core/framework/op.h"
#include "/home/noah/tf/lib/python3.5/site-packages/tensorflow/include/tensorflow/core/framework/shape_inference.h"
#include "/home/noah/tf/lib/python3.5/site-packages/tensorflow/include/tensorflow/core/framework/op_kernel.h"

#include "sky.h"
#include "pointing_vectors.h"
#include "cereal/archives/binary.hpp"

using namespace tensorflow;

REGISTER_OP("Image")
.Input("in: int32")
.Output("out: int32")
.SetShapeFn(
    [](::tensorflow::shape_inference::InferenceContext* c) { c->set_output(0, c->input(0)); return Status::OK(); }
);

class imgop : public OpKernel {

public:

    stars::Sky sky;

    /// *constructor* interfaces with tensorflow, and loads the sky binary file needed to generate star images
    ///
    explicit imgop(OpKernelConstruction* context) : OpKernel(context) {
        std::string datadir = "/home/noah/starid/stars/data/"; // move out of header when possible
        std::ifstream is1(std::string(datadir + "sky"));
        cereal::BinaryInputArchive iarchive1(is1);
        iarchive1(sky);
    }

    /// *compute* called by tensorflow to perform op
    ///
    void Compute(OpKernelContext* context) override;

};

REGISTER_KERNEL_BUILDER(Name("Image").Device(DEVICE_CPU), imgop)

#endif
