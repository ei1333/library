#include "super-link-cut-tree.cpp"

/**
 * @brief Subtree Add Subtree Sum
 */
using T = int64_t;

// 全体への遅延伝搬をするための作用素
struct Lazy {
  T v;

  // 単位元
  Lazy() : v{0} {}

  // 初期化
  Lazy(T v) : v{v} {}

  void propagate(const Lazy &p) { v += p.v; }
};

// Light-edge の情報
template< typename Lazy >
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

  // 部分木への遅延伝搬
  void propagate(const Lazy &p) {
    sum_sum += sz_sum * p.v;
    sum += sz * p.v;
  }
};

// Heavy-edge の情報
template< typename LInfo, typename Lazy >
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

  // 遅延伝搬
  void propagate(const Lazy &p) {
    sum_sum += p.v * sz_sum;
    sum += p.v;
  }

  // light-edgeに対する遅延伝搬
  // pathとsubtreeの遅延伝搬が両方ある場合に実装する
  void propagate_light(const Lazy &p) {}
};

using LCT = SuperLinkCutTree< Info, LInfo, Lazy >;
