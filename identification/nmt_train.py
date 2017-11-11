import tensorflow as tf
from lib.nmt import model as nmt_model
from lib.nmt import model_helper
from lib.nmt.utils import misc_utils as utils
from nmt_config import hparams

scope = None
target_session = ''
skip_count = hparams.batch_size * hparams.epoch_step

model_creator = nmt_model.Model
train_model = model_helper.create_train_model(model_creator, hparams, scope)

config_proto = utils.get_config_proto(log_device_placement=hparams.log_device_placement)
train_sess = tf.Session(target=target_session, config=config_proto, graph=train_model.graph)

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



