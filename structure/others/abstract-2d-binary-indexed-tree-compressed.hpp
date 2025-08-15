#include "abstract-binary-indexed-tree.hpp"

/**
 * @brief Abstract 2D Binary Indexed Tree Compressed(抽象化2次元座圧BIT)
 */
template <typename T, typename F>
struct Abstract2DBinaryIndexedTreeCompressed {
 private:
  int n;
  vector<AbstractBinaryIndexedTree<T, F> > data;
  const F f;
  const T e;
  vector<int> hs;
  vector<vector<int> > beet;

 public:
  Abstract2DBinaryIndexedTreeCompressed(const vector<int>& hs, const F f,
                                        const T& e)
      : n((int)hs.size()), hs(hs), f(f), e(e) {
    vector<int> ord(n);
    iota(begin(ord), end(ord), 0);
    sort(begin(ord), end(ord), [&](int a, int b) { return hs[a] < hs[b]; });
    beet.resize(n + 1);
    for (auto&& i : ord) {
      for (int k = i + 1; k <= n; k += k & -k) {
        beet[k].emplace_back(hs[i]);
      }
    }
    data.reserve(n + 1);
    for (int k = 0; k <= n; k++) {
      beet[k].erase(unique(begin(beet[k]), end(beet[k])), end(beet[k]));
      data.emplace_back((int)beet[k].size(), f, e);
    }
  }

  void apply(int k1, const T& x) {
    int k2 = hs[k1];
    for (++k1; k1 <= n; k1 += k1 & -k1) {
      int p = lower_bound(begin(beet[k1]), end(beet[k1]), k2) - begin(beet[k1]);
      data[k1].apply(p, x);
    }
  }

  T prod(int r1, int r2) const {
    T ret{e};
    for (; r1 > 0; r1 -= r1 & -r1) {
      int p = lower_bound(begin(beet[r1]), end(beet[r1]), r2) - begin(beet[r1]);
      ret = f(ret, data[r1].prod(p));
    }
    return ret;
  }
};

template <typename T, typename F>
Abstract2DBinaryIndexedTreeCompressed<T, F>
get_abstract_2d_binary_indexed_tree_compressed(const vector<int>& hs,
                                               const F& f, const T& e) {
  return Abstract2DBinaryIndexedTreeCompressed{hs, f, e};
}
