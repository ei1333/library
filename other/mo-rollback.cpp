struct MoRollBack {
  using ADD = function< void(int) >;
  using REM = function< void(int) >;
  using RESET = function< void() >;
  using SNAPSHOT = function< void() >;
  using ROLLBACK = function< void() >;

  int width;
  vector< int > left, right, order;

  MoRollBack(int N, int Q) : width((int) sqrt(N)), order(Q) {
    iota(begin(order), end(order), 0);
  }

  void add(int l, int r) { /* [l, r) */
    left.emplace_back(l);
    right.emplace_back(r);
  }

  int run(const ADD &add, const REM &rem, const RESET &reset, const SNAPSHOT &snapshot, const ROLLBACK &rollback) {
    assert(left.size() == order.size());
    sort(begin(order), end(order), [&](int a, int b) {
      int ablock = left[a] / width, bblock = left[b] / width;
      if(ablock != bblock) return ablock < bblock;
      return right[a] < right[b];
    });
    reset();
    for(auto idx : order) {
      if(right[idx] - left[idx] < width) {
        for(int i = left[idx]; i < right[idx]; i++) add(i);
        rem(idx);
        rollback();
      }
    }
    int nr = 0, last_block = -1;
    for(auto idx : order) {
      if(right[idx] - left[idx] < width) continue;
      int block = left[idx] / width;
      if(last_block != block) {
        reset();
        last_block = block;
        nr = (block + 1) * width;
      }
      while(nr < right[idx]) add(nr++);
      snapshot();
      for(int j = (block + 1) * width - 1; j >= left[idx]; j--) add(j);
      rem(idx);
      rollback();
    }
  }
};

