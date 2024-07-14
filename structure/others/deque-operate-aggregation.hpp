template <typename T, typename F>
struct DequeOperateAggregation {
 private:
  struct Node {
    T val, sum;

    Node(const T &val, const T &sum) : val(val), sum(sum) {}
  };
  const F f;
  vector<Node> st[2];

  void rebuild() {
    if (not st[0].empty()) {
      st[0][0].sum = st[0][0].val;
      for (int i = 1; i < (int)st[0].size(); i++) {
        st[0][i].sum = f(st[0][i].val, st[0][i - 1].sum);
      }
    }
    if (not st[1].empty()) {
      st[1][0].sum = st[1][0].val;
      for (int i = 1; i < (int)st[1].size(); i++) {
        st[1][i].sum = f(st[1][i - 1].sum, st[1][i].val);
      }
    }
  }

 public:
  DequeOperateAggregation() = default;

  explicit DequeOperateAggregation(F f) : f(f) {}

  bool empty() const { return st[0].empty() and st[1].empty(); }

  size_t size() const { return st[0].size() + st[1].size(); }

  T all_prod() const {
    assert(not empty());
    if (st[0].empty()) {
      return st[1].back().sum;
    } else if (st[1].empty()) {
      return st[0].back().sum;
    } else {
      return f(st[0].back().sum, st[1].back().sum);
    }
  }

  void push_front(const T &x) {
    if (st[0].empty()) {
      st[0].emplace_back(x, x);
    } else {
      st[0].emplace_back(x, f(x, st[0].back().sum));
    }
  }

  void push_back(const T &x) {
    if (st[1].empty()) {
      st[1].emplace_back(x, x);
    } else {
      st[1].emplace_back(x, f(st[1].back().sum, x));
    }
  }

  void pop_front() {
    assert(not empty());
    if (st[0].empty()) {
      auto m = st[1].size() / 2;
      st[0] = {st[1].rbegin() + m, st[1].rend()};
      st[1] = {st[1].end() - m, st[1].end()};
      rebuild();
    }
    st[0].pop_back();
  }

  void pop_back() {
    assert(not empty());
    if (st[1].empty()) {
      auto m = st[0].size() / 2;
      st[1] = {st[0].rbegin() + m, st[0].rend()};
      st[0] = {st[0].end() - m, st[0].end()};
      rebuild();
    }
    st[1].pop_back();
  }
};

template <typename T, typename F>
DequeOperateAggregation<T, F> get_deque_operate_aggregation(const F &f) {
  return DequeOperateAggregation<T, F>{f};
}
