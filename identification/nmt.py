### *neural machine translation* nmt using languages based on libstarid, and tensorflow training and inference
###
import tensorflow as tf
import os
from lib.nmt import model as nmt_model
from lib.nmt import model_helper
from lib.nmt import train
from lib.nmt import inference
from lib.nmt.utils import misc_utils as utils
from nmt_config import hparams
global hparams

def train_minimalist():
    model_creator = nmt_model.Model
    train_model = model_helper.create_train_model(model_creator, hparams)
    train_sess = tf.Session(config=utils.get_config_proto(log_device_placement=hparams.log_device_placement), graph=train_model.graph)
    with train_model.graph.as_default():
        loaded_train_model, global_step = model_helper.create_or_load_model(train_model.model, hparams.out_dir, train_sess, 'train')
    summary_writer = tf.summary.FileWriter(os.path.join(hparams.out_dir, 'train_log'), train_model.graph)
    train_sess.run(train_model.iterator.initializer, feed_dict={train_model.skip_count_placeholder: (hparams.batch_size * hparams.epoch_step)})
    global_step = 0
    while global_step < hparams.num_train_steps:
        try:
            (_, step_loss, step_predict_count, step_summary, global_step, step_word_count, batch_size) = loaded_train_model.train(train_sess)
            global_step += 1
        except tf.errors.OutOfRangeError:
            utils.print_out('# epoch completed, step %d' % global_step)
            train_sess.run(train_model.iterator.initializer, feed_dict={train_model.skip_count_placeholder: 0})
            continue
    summary_writer.add_summary(step_summary, global_step)
    loaded_train_model.saver.save(train_sess, os.path.join(hparams.out_dir, 'checkpoint.ckpt'), global_step=global_step)
    summary_writer.close()

def eval_minimalist():
    model_creator = nmt_model.Model
    train_model = model_helper.create_train_model(model_creator, hparams)
    eval_model = model_helper.create_eval_model(model_creator, hparams)
    train_sess = tf.Session(config=utils.get_config_proto(log_device_placement=hparams.log_device_placement), graph=train_model.graph)
    eval_sess = tf.Session(config=utils.get_config_proto(log_device_placement=hparams.log_device_placement), graph=eval_model.graph)
    with train_model.graph.as_default():
        loaded_train_model, global_step = model_helper.create_or_load_model(train_model.model, hparams.out_dir, train_sess, 'train')
    summary_writer = tf.summary.FileWriter(os.path.join(hparams.out_dir, 'train_log'), train_model.graph)
    train_sess.run(train_model.iterator.initializer, feed_dict={train_model.skip_count_placeholder: (hparams.batch_size * hparams.epoch_step)})
    train.run_internal_eval(eval_model, eval_sess, hparams.out_dir, hparams, summary_writer)
    global_step = 0
    while global_step < hparams.num_train_steps:
        try:
            (_, step_loss, step_predict_count, step_summary, global_step, step_word_count, batch_size) = loaded_train_model.train(train_sess)
            global_step += 1
        except tf.errors.OutOfRangeError:
            utils.print_out('# epoch completed, step %d' % global_step)
            train_sess.run(train_model.iterator.initializer, feed_dict={train_model.skip_count_placeholder: 0})
            continue
    train.run_internal_eval(eval_model, eval_sess, hparams.out_dir, hparams, summary_writer)
    summary_writer.add_summary(step_summary, global_step)
    loaded_train_model.saver.save(train_sess, os.path.join(hparams.out_dir, 'checkpoint.ckpt'), global_step=global_step)
    summary_writer.close()

def infer_minimalist():
    model_creator = nmt_model.Model
    infer_model = model_helper.create_infer_model(model_creator, hparams)
    dev_src_file = "%s.%s" % (hparams.dev_prefix, hparams.src)
    dev_tgt_file = "%s.%s" % (hparams.dev_prefix, hparams.tgt)
    sample_src_data = inference.load_data(dev_src_file)
    sample_tgt_data = inference.load_data(dev_tgt_file)
    infer_sess = tf.Session(config=utils.get_config_proto(log_device_placement=hparams.log_device_placement), graph=infer_model.graph)
    with infer_model.graph.as_default():
        loaded_infer_model, global_step = model_helper.create_or_load_model(infer_model.model, hparams.out_dir, infer_sess, 'infer')
    infer_sess.run(infer_model.iterator.initializer, feed_dict={infer_model.src_placeholder: sample_src_data, infer_model.batch_size_placeholder: hparams.infer_batch_size})
    summary_writer = tf.summary.FileWriter(os.path.join(hparams.out_dir, 'infer_log'), infer_model.graph)
    train.run_sample_decode(infer_model, infer_sess, hparams.out_dir, hparams, summary_writer, sample_src_data, sample_tgt_data)
    train.run_external_eval(infer_model, infer_sess, hparams.out_dir, hparams, summary_writer)
    summary_writer.close()

if __name__ == '__main__':
    if not tf.gfile.Exists(hparams.out_dir): tf.gfile.MakeDirs(hparams.out_dir)
    # train_minimalist()
    # eval_minimalist()
    infer_minimalist()

