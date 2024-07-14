template <typename T, typename F>
struct QueueOperateAggregation {
 private:
  struct Node {
    T val, sum;

    Node(const T& val, const T& sum) : val(val), sum(sum) {}
  };
  const F f;
  vector<Node> st[2];

 public:
  QueueOperateAggregation() = default;

  explicit QueueOperateAggregation(F f) : f(f) {}

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

  void push(const T& x) {
    if (st[1].empty()) {
      st[1].emplace_back(x, x);
    } else {
      st[1].emplace_back(x, f(st[1].back().sum, x));
    }
  }

  void pop() {
    assert(not empty());
    if (st[0].empty()) {
      st[0].emplace_back(st[1].back().val, st[1].back().val);
      st[1].pop_back();
      while (not st[1].empty()) {
        st[0].emplace_back(st[1].back().val,
                           f(st[1].back().val, st[0].back().sum));
        st[1].pop_back();
      }
    }
    st[0].pop_back();
  }
};

template <typename T, typename F>
QueueOperateAggregation<T, F> get_queue_operate_aggregation(const F& f) {
  return QueueOperateAggregation<T, F>{f};
}
