/**
 * @brief CumulativeSum(一次元累積和)
 * @docs docs/cumulative-sum.md
 */
template< class T >
struct CumulativeSum {
  vector< T > data;

  CumulativeSum() = default;

  explicit CumulativeSum(size_t sz) : data(sz, 0) {}

  void add(int k, const T &x) {
    data[k] += x;
  }

  void build() {
    for(int i = 1; i < data.size(); i++) {
      data[i] += data[i - 1];
    }
  }

  T query(int k) const {
    if(k < 0) return 0;
    return data[min(k, (int) data.size() - 1)];
  }
};
