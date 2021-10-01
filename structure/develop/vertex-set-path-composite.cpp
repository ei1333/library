#include "super-link-cut-tree.cpp"
#include "../../math/combinatorics/montgomery-mod-int.cpp"

/**
 * @brief Vertex Set Path Composite
 */
using T = MontgomeryModInt< 998244353, true >;

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

  // 単位元(キーの値はアクセスしないので未初期化でもよい
  LInfo() {}

  // 初期化
  LInfo(T v) {}

  // l, r は Splay-tree の子 (原理上、各ノード区別はない)
  void update(const LInfo &l, const LInfo &r) {}

  // 部分木への遅延伝搬
  void propagate(const Lazy &p) {}
};

// Heavy-edge の情報
template< typename LInfo, typename Lazy >
struct Info {
  T a, b; // ax+b

  T a_sum_p, b_sum_p;
  T a_sum_c, b_sum_c;


  // 単位元(キーの値はアクセスしないので未初期化でもよい
  Info() : a_sum_p{1}, b_sum_p{0}, a_sum_c{1}, b_sum_c{0} {}

  // 初期化
  Info(T a, T b) : a(a), b(b) {}

  // 反転
  void toggle() {
    swap(a_sum_p, a_sum_c);
    swap(b_sum_p, b_sum_c);
  }

  // pが親, cがheavy-edgeで結ばれた子, lがそれ以外の子
  void update(const Info &p, const Info &c, const LInfo &l) {
    a_sum_p = p.a_sum_p * a * c.a_sum_p;
    b_sum_p = (p.b_sum_p * a + b) * c.a_sum_p + c.b_sum_p;

    a_sum_c = c.a_sum_c * a * p.a_sum_c;
    b_sum_c = (c.b_sum_c * a + b) * p.a_sum_c + p.b_sum_c;
  }

  // 親と light-edge で繋げる
  LInfo link() const { return LInfo(); }

  // 遅延伝搬
  void propagate(const Lazy &p) {}

  // light-edgeに対する遅延伝搬
  // pathとsubtreeの遅延伝搬が両方ある場合に実装する
  void propagate_light(const Lazy &p) {}
};

using LCT = SuperLinkCutTree< Info, LInfo, Lazy >;
