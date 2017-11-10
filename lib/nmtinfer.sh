#!/usr/bin/env bash

#cat > /tmp/my_infer_file.vi
#(copy and paste some sentences from /tmp/nmt_data/tst2013.vi)

python3.6 -m nmt.nmt \
    --out_dir=/tmp/nmt_model \
    --inference_input_file=/tmp/my_infer_file.vi \
    --inference_output_file=/tmp/nmt_model/output_infer

cat /tmp/nmt_model/output_infer # To view the inference as output