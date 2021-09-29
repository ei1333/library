#include "super-link-cut-tree.cpp"

/**
 * @brief Subtree Add Subtree Sum
 */
using T = int64_t;

// 全体への遅延伝搬をするための作用素
struct AllLazy {
  T v;

  // 単位元
  AllLazy() : v{0} {}

  // 初期化
  AllLazy(T v) : v{v} {}

  void propagate(const AllLazy &p) { v += p.v; }
};

// パスへの遅延伝搬をする作用素
struct PathLazy {

  // 単位元
  PathLazy() {}

  // 初期化
  PathLazy(T v) {}

  void propagate(const PathLazy &p) {}
};

// Light-edge の情報
template< typename AllLazy >
struct LInfo {
  T sum;
  int sz;

  T sum_sum;
  int sz_sum;

  // 単位元(キーの値はアクセスしないので未初期化でもよい
  LInfo() : sum_sum{0}, sz_sum{0} {}

  // 初期化
  LInfo(T sum, int sz) : sum{sum}, sz{sz} {}

  // l, r は Splay-tree の子 (原理上、各ノード区別はない)
  void update(const LInfo &l, const LInfo &r) {
    sum_sum = l.sum_sum + sum + r.sum_sum;
    sz_sum = l.sz_sum + sz + r.sz_sum;
  }

  // 全体への遅延伝搬
  void propagate(const AllLazy &p) {
    sum_sum += sz_sum * p.v;
    sum += sz * p.v;
  }
};

// Heavy-edge の情報
template< typename LInfo, typename AllLazy, typename PathLazy >
struct Info {
  T sum;

  T sum_sum;
  int sz_sum;

  // 単位元(キーの値はアクセスしないので未初期化でもよい
  Info() : sum_sum{0}, sz_sum{0} {}

  // 初期化
  Info(T sum) : sum{sum} {}

  // 反転
  void toggle() {}

  // pが親, cがheavy-edgeで結ばれた子, lがそれ以外の子
  void update(const Info &p, const Info &c, const LInfo &l) {
    sum_sum = p.sum_sum + sum + (c.sum_sum + l.sum_sum);
    sz_sum = p.sz_sum + 1 + (c.sz_sum + l.sz_sum);
  }

  // 親と light-edge で繋げる
  LInfo link() const { return LInfo(sum_sum, sz_sum); }

  // 全体への遅延伝搬
  void propagate_all(const AllLazy &p) {
    sum_sum += p.v * sz_sum;
    sum += p.v;
  }

  // パスの遅延伝搬
  void propagate_path(const PathLazy &p) {}
};

using LCT = SuperLinkCutTree< Info, LInfo, AllLazy, PathLazy >;
