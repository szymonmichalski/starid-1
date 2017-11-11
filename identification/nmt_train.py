import tensorflow as tf
from lib.nmt import model as nmt_model
from lib.nmt import model_helper
from lib.nmt.utils import iterator_utils
from lib.nmt.utils import misc_utils as utils
from lib.nmt.utils import vocab_utils
import nmt_config
global hparams

scope = None
target_session = ''

model_creator = nmt_model.Model
train_model = model_helper.create_train_model(model_creator, hparams, scope)

config_proto = utils.get_config_proto(log_device_placement=hparams.log_device_placement)
train_sess = tf.Session(target=target_session, config=config_proto, graph=train_model.graph)

with train_model.graph.as_default():
    loaded_train_model, global_step = model_helper.create_or_load_model(train_model.model, hparams.model_dir, train_sess, 'train')

skip_count = hparams.batch_size * hparams.epoch_step
train_sess.run(train_model.iterator.initializer, feed_dict={train_model.skip_count_placeholder: skip_count})

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



