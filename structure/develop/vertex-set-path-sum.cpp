#include "super-link-cut-tree.cpp"

/**
 * @brief Vertex Set Path Sum
 */
using T = int64_t;

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
  T v;

  T sum;


  // 単位元(キーの値はアクセスしないので未初期化でもよい
  Info() : sum{0} {}

  // 初期化
  Info(T v) : v{v} {}

  // 反転
  void toggle() {}

  // pが親, cがheavy-edgeで結ばれた子, lがそれ以外の子
  void update(const Info &p, const Info &c, const LInfo &l) {
    sum = p.sum + v + c.sum;
  }

  // 親と light-edge で繋げる
  LInfo link() const { return LInfo(); }

  // 全体への遅延伝搬
  void propagate_all(const AllLazy &p) {}

  // パスの遅延伝搬
  void propagate_path(const PathLazy &p) {}
};

using LCT = SuperLinkCutTree< Info, LInfo, AllLazy, PathLazy >;
