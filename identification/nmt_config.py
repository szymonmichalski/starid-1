import tensorflow as tf
from lib.nmt.utils import vocab_utils
from lib.nmt.utils import misc_utils as utils
global hparams

hparams = tf.contrib.training.HParams(
    src='geom',
    tgt='ids',
    train_prefix='/tmp/nmt_data/train',
    dev_prefix='/tmp/nmt_data/test1',
    test_prefix='/tmp/nmt_data/test2',
    vocab_prefix='/tmp/nmt_data/vocab',
    out_dir='/tmp/nmt_model',

    num_units=32,
    num_layers=2,
    dropout=0.2,
    unit_type='lstm',
    encoder_type='uni',
    residual=False,
    time_major=True,
    num_embeddings_partitions=0,

    attention='',
    attention_architecture='standard',
    pass_hidden_state=True,

    optimizer='sgd',
    num_train_steps=1000,
    batch_size=128,
    init_op='uniform',
    init_weight=0.1,
    max_gradient_norm=5.0,
    learning_rate=1.0,
    warmup_steps=0,
    warmup_scheme='t2t',
    start_decay_step=0,
    decay_factor=1.0,
    decay_steps=10000,
    learning_rate_decay_scheme='',
    colocate_gradients_with_ops=True,

    num_buckets=5,
    max_train=0,
    src_max_len=50,
    tgt_max_len=50,
    source_reverse=True,

    sos='<s>',
    eos='</s>',
    subword_option='',
    check_special_token=True,

    forget_bias=1.0,
    num_gpus=1,
    epoch_step=0,
    steps_per_stats=100,
    steps_per_external_eval=None,
    share_vocab=False,
    metrics='bleu',
    log_device_placement=False,
    random_seed=None,
    override_loaded_hparams=False,
)

src_vocab_file = hparams.vocab_prefix + "." + hparams.src
tgt_vocab_file = hparams.vocab_prefix + "." + hparams.tgt

src_vocab_size, src_vocab_file = vocab_utils.check_vocab(
    src_vocab_file,
    hparams.out_dir,
    check_special_token=hparams.check_special_token,
    sos=hparams.sos,
    eos=hparams.eos,
    unk=vocab_utils.UNK)

tgt_vocab_size, tgt_vocab_file = vocab_utils.check_vocab(
    tgt_vocab_file,
    hparams.out_dir,
    check_special_token=hparams.check_special_token,
    sos=hparams.sos,
    eos=hparams.eos,
    unk=vocab_utils.UNK)

hparams.add_hparam("src_vocab_size", src_vocab_size)
hparams.add_hparam("tgt_vocab_size", tgt_vocab_size)
hparams.add_hparam("src_vocab_file", src_vocab_file)
hparams.add_hparam("tgt_vocab_file", tgt_vocab_file)

if not tf.gfile.Exists(hparams.out_dir):
    utils.print_out("# Creating output directory %s ..." % hparams.out_dir)
    tf.gfile.MakeDirs(hparams.out_dir)