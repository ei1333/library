struct ChronoTimer {
  chrono::high_resolution_clock::time_point st;

  ChronoTimer() { reset(); }

  void reset() {
    st = chrono::high_resolution_clock::now();
  }

  chrono::milliseconds::rep elapsed() {
    auto ed = chrono::high_resolution_clock::now();
    return chrono::duration_cast< chrono::milliseconds >(ed - st).count();
  }
};
