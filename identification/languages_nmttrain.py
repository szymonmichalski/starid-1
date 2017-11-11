import tensorflow as tf
from ..lib.nmt.utils import iterator_utils
from ..lib.nmt.utils import misc_utils as utils
from ..lib.nmt.utils import vocab_utils



# train_model = model_helper.create_train_model(model_creator, hparams, scope)

src_file = "%s.%s" % (hparams.train_prefix, hparams.src)
tgt_file = "%s.%s" % (hparams.train_prefix, hparams.tgt)
src_vocab_file = hparams.src_vocab_file
tgt_vocab_file = hparams.tgt_vocab_file

graph = tf.Graph()

with graph.as_default(), tf.container(scope or "train"):
    src_vocab_table, tgt_vocab_table = vocab_utils.create_vocab_tables(
        src_vocab_file, tgt_vocab_file, hparams.share_vocab)

    src_dataset = tf.data.TextLineDataset(src_file)
    tgt_dataset = tf.data.TextLineDataset(tgt_file)
    skip_count_placeholder = tf.placeholder(shape=(), dtype=tf.int64)

    iterator = iterator_utils.get_iterator()


    # train_sess = tf.Session(target=target_session, config=config_proto, graph=train_model.graph)
#
# while global_step < num_train_steps:
#     try:
#       step_result = loaded_train_model.train(train_sess)
#       (_, step_loss, step_predict_count, step_summary, global_step,
#        step_word_count, batch_size) = step_result
#       hparams.epoch_step += 1
#     except tf.errors.OutOfRangeError:
#       # Finished going through the training dataset.  Go to next epoch.
#       train_sess.run(
#           train_model.iterator.initializer,
#           feed_dict={train_model.skip_count_placeholder: 0})
#       continue



