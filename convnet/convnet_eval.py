with tf.name_scope('evaluate'):
    with tf.name_scope('correct_prediction'):
        correct_prediction = tf.equal(tf.argmax(y_conv,1), tf.argmax(y_,1))
    with tf.name_scope('accuracy'):
        accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
        tf.scalar_summary('accuracy', accuracy)

        merged = tf.merge_all_summaries()
        train_writer = tf.train.SummaryWriter('/tmp/convnet_logs' + '/train', sess.graph)
        sess.run(tf.initialize_all_variables())

    for i in range(1000):
        batch = input.train.next_batch(50)
        if i%100 == 0:
            train_accuracy = accuracy.eval(feed_dict={x:batch[0], y_: batch[1], keep_prob: 1.0})
            print("step %d, training accuracy %g"%(i, train_accuracy))
            summary, _ = sess.run([merged, train_step], feed_dict={x: batch[0], y_: batch[1], keep_prob: 0.5})
            train_writer.add_summary(summary, i)

print("test accuracy %g"%accuracy.eval(feed_dict={x: input.test.images, y_: input.test.labels, keep_prob: 1.0}))