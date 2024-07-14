struct Mo {
 private:
  int n, w;
  vector<int> ord;
  vector<pair<int, int> > lr;

 public:
  Mo(int n, int q) : n(n), ord(q) {
    w = max<int>(1, n / max(1.0, sqrt(q * 2.0 / 3.0)));
    iota(ord.begin(), ord.end(), 0);
    lr.reserve(q);
  }

  void add_query(int l, int r) {
    assert(0 <= l and l < r and r <= n);
    lr.emplace_back(l, r);
  }

  template <typename AL, typename AR, typename EL, typename ER, typename Q>
  void calclate_queries(const AL &add_left, const AR &add_right,
                        const EL &erase_left, const ER &erase_right,
                        const Q &query) {
    assert(lr.size() == ord.size());
    vector<int> bs(n);
    for (int i = 0, cnt = 0, b = 0; i < n; i++) {
      bs[i] = b;
      if (++cnt == w) {
        ++b;
        cnt = 0;
      }
    }
    sort(ord.begin(), ord.end(), [&](int a, int b) {
      int a_block = bs[lr[a].first];
      int b_block = bs[lr[b].first];
      if (a_block != b_block) return a_block < b_block;
      if (a_block & 1)
        return lr[a].second < lr[b].second;
      else
        return lr[a].second > lr[b].second;
    });
    int l = 0, r = 0;
    for (auto idx : ord) {
      while (l > lr[idx].first) add_left(--l);
      while (r < lr[idx].second) add_right(r++);
      while (l < lr[idx].first) erase_left(l++);
      while (r > lr[idx].second) erase_right(--r);
      query(idx);
    }
  }

  template <typename A, typename E, typename Q>
  void calclate_queries(const A &add, const E &erase, const Q &query) {
    calclate_queries(add, add, erase, erase, query);
  }
};
