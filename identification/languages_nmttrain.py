import tensorflow as tf

# train_model = model_helper.create_train_model(model_creator, hparams, scope)
#
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



