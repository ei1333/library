#include "super-link-cut-tree.cpp"

/**
 * @brief Vertex Set Subtree Sum
 */
using T = int64_t;

// 遅延伝搬をするための作用素
struct Lazy {

  // 単位元
  Lazy() {}

  // 初期化
  Lazy(T v) {}

  // 遅延伝搬
  void propagate(const Lazy &p) {}
};

// Light-edge の情報
template< typename Lazy >
struct LInfo {
  T sum;

  T sum_sum;

  // 単位元(キーの値はアクセスしないので未初期化でもよい
  LInfo() : sum_sum{0} {}

  // 初期化
  LInfo(T sum) : sum{sum} {}

  // l, r は Splay-tree の子 (原理上、各ノード区別はない)
  void update(const LInfo &l, const LInfo &r) {
    sum_sum = l.sum_sum + sum + r.sum_sum;
  }

  // 部分木への遅延伝搬
  void propagate(const Lazy &p) {}
};

// Heavy-edge の情報
template< typename LInfo, typename Lazy >
struct Info {
  T sum;

  T sum_sum;

  // 単位元(キーの値はアクセスしないので未初期化でもよい
  Info() : sum_sum{0} {}

  // 初期化
  Info(T sum) : sum{sum} {}

  // 反転
  void toggle() {}

  // pが親, cがheavy-edgeで結ばれた子, lがそれ以外の子
  void update(const Info &p, const Info &c, const LInfo &l) {
    sum_sum = p.sum_sum + sum + (c.sum_sum + l.sum_sum);
  }

  // 親と light-edge で繋げる
  LInfo link() const { return LInfo(sum_sum); }

  // 遅延伝搬
  void propagate(const Lazy &p) {}

  // light-edgeに対する遅延伝搬
  // pathとsubtreeの遅延伝搬が両方ある場合に実装する
  void propagate_light(const Lazy &p) {}
};

using LCT = SuperLinkCutTree< Info, LInfo, Lazy >;
