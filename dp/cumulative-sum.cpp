template< class T >
struct CumulativeSum {
  vector< T > data;

  CumulativeSum(int sz) : data(sz, 0) {};

  void add(int k, T x) {
    data[k] += x;
  }

  void build() {
    for(int i = 1; i < data.size(); i++) {
      data[i] += data[i - 1];
    }
  }

  T query(int k) {
    if(k < 0) return (0);
    return (data[min(k, (int) data.size() - 1)]);
  }
};
