/**
 * @brief Abstract Binary Indexed Tree(抽象化BIT)
 * @docs docs/abstract-binary-indexed-tree.md
 */
template< typename T, typename F >
struct AbstractBinaryIndexedTree {
private:
  int n;
  vector< T > data;
  const F f;
  const T e;

public:
  AbstractBinaryIndexedTree() = default;

  explicit AbstractBinaryIndexedTree(int n, const F f, const T &e) : n(n), f(f), e(e) {
    data.assign(n + 1, e);
  }

  explicit AbstractBinaryIndexedTree(const vector< T > &v, const F f, const T &e) :
      AbstractBinaryIndexedTree((int) v.size(), f, e) {
    build(v);
  }

  void build(const vector< T > &v) {
    assert(n == (int) v.size());
    for(int i = 1; i <= n; i++) data[i] = v[i - 1];
    for(int i = 1; i <= n; i++) {
      int j = i + (i & -i);
      if(j <= n) data[j] = f(data[j], data[i]);
    }
  }

  void apply(int k, const T &x) {
    for(++k; k <= n; k += k & -k) data[k] = f(data[k], x);
  }

  T prod(int r) const {
    T ret{e};
    for(; r > 0; r -= r & -r) ret = f(ret, data[r]);
    return ret;
  }
};

template< typename T, typename F >
AbstractBinaryIndexedTree< T, F > get_abstract_binary_indexed_tree(int n, const F &f, const T &e) {
  return AbstractBinaryIndexedTree{n, f, e};
}

template< typename T, typename F >
AbstractBinaryIndexedTree< T, F > get_abstract_binary_indexed_tree(const vector< T > &v, const F &f, const T &e) {
  return AbstractBinaryIndexedTree{v, f, e};
}
