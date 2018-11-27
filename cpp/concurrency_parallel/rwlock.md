```
class rwlock {
  mutex mu;
  condition_variable cv;
  atomic<int> reader;
  atomic<bool> writer;
public:
  rwlock() {
    writer.store(false, memory_order_seq_cst);
  }

  void read_lock() {
    unique_lock ul(mu);
    while (writer)
      cv.wait(ul);
    reader++;
  }

  void read_unlock() {
    unique_lock ul(mu);
    reader--;
    if (reader == 0) // if all readers are done, notify writer
      cv.notify_all();
  }

  void write_lock() {
    unique_lock ul(mu);
    while (writer || reader > 0) // if there are other writers, or readers are not done, WAIT!
      cv.wait(ul);
    writer.store(true, memory_order_seq_cst);
  }

  void write_unlock() {
    //if(!writer) return;
    unique_lock ul(mu);
    writer.store(false, memory_order_seq_cst);
    cv.notify_all();
  }
};
```