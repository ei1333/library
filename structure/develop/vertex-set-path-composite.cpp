#include "super-link-cut-tree.cpp"
#include "../../math/combinatorics/montgomery-mod-int.cpp"

/**
 * @brief Vertex Set Path Composite
 */
using T = MontgomeryModInt< 998244353, true >;

// 全体への遅延伝搬をするための作用素
struct AllLazy {

  // 単位元
  AllLazy() {}

  // 初期化
  AllLazy(T v) {}

  void propagate(const AllLazy &p) {}
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

  // 単位元(キーの値はアクセスしないので未初期化でもよい
  LInfo() {}

  // 初期化
  LInfo(T v) {}

  // l, r は Splay-tree の子 (原理上、各ノード区別はない)
  void update(const LInfo &l, const LInfo &r) {}

  // 全体への遅延伝搬
  void propagate(const AllLazy &p) {}
};

// Heavy-edge の情報
template< typename LInfo, typename AllLazy, typename PathLazy >
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

  // 全体への遅延伝搬
  void propagate_all(const AllLazy &p) {}

  // パスの遅延伝搬
  void propagate_path(const PathLazy &p) {}
};

using LCT = SuperLinkCutTree< Info, LInfo, AllLazy, PathLazy >;
