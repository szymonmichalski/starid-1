import tensorflow as tf
from lib.nmt import model as nmt_model
from lib.nmt import model_helper
from lib.nmt.utils import misc_utils as utils
from nmt_config import hparams
global hparams

model_creator = nmt_model.Model
train_model = model_helper.create_train_model(model_creator, hparams)

config_proto = utils.get_config_proto(log_device_placement=hparams.log_device_placement)
train_sess = tf.Session(target='', config=config_proto, graph=train_model.graph)

with train_model.graph.as_default():
    loaded_train_model, global_step = model_helper.create_or_load_model(
        train_model.model, hparams.out_dir, train_sess, 'train')

skip_count = hparams.batch_size * hparams.epoch_step
train_sess.run(train_model.iterator.initializer, feed_dict={train_model.skip_count_placeholder: skip_count})

global_step = 0
while global_step < hparams.num_train_steps:
    try:
        step_result = loaded_train_model.train(train_sess)
        (_, step_loss, step_predict_count, step_summary, global_step, step_word_count, batch_size) = step_result
        global_step += 1
    except tf.errors.OutOfRangeError:
        utils.print_out('# finished an epoch, step %d' % global_step)
        train_sess.run(train_model.iterator.initializer, feed_dict={train_model.skip_count_placeholder: 0})
        continue
