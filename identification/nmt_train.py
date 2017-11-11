import tensorflow as tf
from lib.nmt import model as nmt_model
from lib.nmt import model_helper
from lib.nmt.utils import misc_utils as utils
from nmt_config import hparams
global hparams

model_creator = nmt_model.Model

scope = None
train_model = model_helper.create_train_model(model_creator, hparams, scope)
# train_model = model_helper.create_train_model(model_creator, hparams)

config_proto = utils.get_config_proto(log_device_placement=hparams.log_device_placement)
target_session = ''
train_sess = tf.Session(target=target_session, config=config_proto, graph=train_model.graph)
# train_sess = tf.Session(graph=train_model.graph)

skip_count = hparams.batch_size * hparams.epoch_step
train_sess.run(train_model.iterator.initializer, feed_dict={train_model.skip_count_placeholder: skip_count})

global_step = 0
while global_step < hparams.num_train_steps:
    try:
      step_result = train_model.train(train_sess)
      (_, step_loss, step_predict_count, step_summary, global_step, step_word_count, batch_size) = step_result
      global_step += 1
    except tf.errors.OutOfRangeError:
      train_sess.run(train_model.iterator.initializer, feed_dict={train_model.skip_count_placeholder: 0})
      continue



