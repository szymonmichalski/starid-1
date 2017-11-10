#!/usr/bin/env bash
#ln -s /tmp/nmt_model model
#ln -s /tmp/nmt_data data
#mkdir /tmp/nmt_data_starid
#ln -s /tmp/nmt_data_starid data_starid
#ln -s $DIRMODEL model
DIRMODEL="/tmp/nmt_model"
#rm -rf $DIRMODEL
rm $DIRMODEL/hparams
mkdir $DIRMODEL
python3.6 -m nmt.nmt \
    --src=geom --tgt=ids \
    --vocab_prefix=/tmp/nmt_data_starid/vocab  \
    --train_prefix=/tmp/nmt_data_starid/train \
    --dev_prefix=/tmp/nmt_data_starid/test1  \
    --test_prefix=/tmp/nmt_data_starid/test2 \
    --out_dir=$DIRMODEL \
    --num_train_steps=4000 \
    --steps_per_stats=100 \
    --num_layers=2 \
    --num_units=128 \
    --dropout=0.2 \
    --metrics=bleu

#python3.6 -m nmt.nmt \
#    --src=vi --tgt=en \
#    --vocab_prefix=/tmp/nmt_data/vocab  \
#    --train_prefix=/tmp/nmt_data/train \
#    --dev_prefix=/tmp/nmt_data/tst2012  \
#    --test_prefix=/tmp/nmt_data/tst2013 \
#    --out_dir=$DIRMODEL \
#    --num_train_steps=300 \
#    --steps_per_stats=100 \
#    --num_layers=2 \
#    --num_units=128 \
#    --dropout=0.2 \
#    --metrics=bleu

#python3.6 -m nmt.nmt \
#    --src=vi --tgt=en \
#    --vocab_prefix=/tmp/nmt_data/vocab  \
#    --train_prefix=/tmp/nmt_data/train \
#    --dev_prefix=/tmp/nmt_data/tst2012  \
#    --test_prefix=/tmp/nmt_data/tst2013 \
#    --out_dir=/tmp/nmt_model \
#    --num_train_steps=12000 \
#    --steps_per_stats=100 \
#    --num_layers=2 \
#    --num_units=128 \
#    --dropout=0.2 \
#    --metrics=bleu