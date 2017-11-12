#!/usr/bin/env bash
#ln -s /home/noah/nmt_model model
#ln -s /home/noah/nmt_data data
#ln -s $DIRMODEL model
DIRMODEL="model"
#rm -rf $DIRMODEL
rm $DIRMODEL/hparams
mkdir $DIRMODEL
python3.6 -m nmt.nmt \
    --src=geom --tgt=ids \
    --vocab_prefix=data/vocab  \
    --train_prefix=data/train \
    --dev_prefix=data/test1  \
    --test_prefix=data/test2 \
    --out_dir=$DIRMODEL \
    --num_train_steps=2000 \
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