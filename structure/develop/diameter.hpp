#include "super-link-cut-tree.hpp"

/**
 * @brief Diameter
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
  T dia, dep;

  T dia_max, dep_max, dep_max2;

  // 単位元(キーの値はアクセスしないので未初期化でもよい
  LInfo() : dia_max(-infll), dep_max(-infll), dep_max2(-infll) {}

  // 初期化
  LInfo(T dia, T dep) : dia(dia), dep(dep) {}

  // l, r は Splay-tree の子 (原理上、各ノード区別はない)
  void update(const LInfo &l, const LInfo &r) {
    dia_max = max({l.dia_max, r.dia_max, dia});
    if(dep < l.dep_max) {
      dep_max2 = max(l.dep_max2, dep);
      dep_max = l.dep_max;
    } else {
      dep_max2 = l.dep_max;
      dep_max = dep;
    }
    if(dep_max < r.dep_max) {
      dep_max2 = max(dep_max, r.dep_max2);
      dep_max = r.dep_max;
    } else {
      dep_max2 = max(dep_max2, r.dep_max);
    }
  }

  // 部分木への遅延伝搬
  void propagate(const Lazy &p) {}
};

// Heavy-edge の情報
template< typename LInfo, typename Lazy >
struct Info {
  T cost;

  T dia_max, p_len, c_len, all;

  // 単位元(キーの値はアクセスしないので未初期化でもよい
  Info() : dia_max(0), p_len(0), c_len(0), all(0) {}

  // 初期化
  Info(T v) : cost(v) {}

  // 反転
  void toggle() {
    swap(p_len, c_len);
  }

  // pが親, cがheavy-edgeで結ばれた子, lがそれ以外の子
  void update(const Info &p, const Info &c, const LInfo &l) {
    all = p.all + cost + c.all;
    p_len = max({p.p_len, p.all + cost + max(l.dep_max, c.p_len)});
    c_len = max({c.c_len, c.all + cost + max(l.dep_max, p.c_len)});
    dia_max = max({p.dia_max, c.dia_max, l.dia_max,
                   l.dep_max + cost + l.dep_max2,
                   p.c_len + cost + max(l.dep_max, c.p_len),
                   l.dep_max + cost + c.p_len});
  }

  // 親と light-edge で繋げる
  LInfo link() const { return LInfo(dia_max, p_len); }

  // 遅延伝搬
  void propagate(const Lazy &p) {}

  // light-edgeに対する遅延伝搬
  // pathとsubtreeの遅延伝搬が両方ある場合に実装する
  void propagate_light(const Lazy &p) {}
};

using LCT = SuperLinkCutTree< Info, LInfo, Lazy >;
