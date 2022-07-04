#include "super-link-cut-tree.cpp"

/**
 * @brief Dynamic Tree Test
 * @see https://dmoj.ca/problem/ds5
 */
using T = int;
const T inf_max = numeric_limits< T >::max();
const T inf_min = numeric_limits< T >::min();

// 遅延伝搬をする作用素
struct Lazy {
  int type; // 0: none, 1: change, 2:inc
  T v;

  // 単位元
  Lazy() : type(0) {}

  // 初期化
  constexpr Lazy(int type, T v) : type(type), v(v) {}

  inline constexpr void propagate(const Lazy &p) {
    if(p.type == 0) {
      return;
    }
    if(type == 0 or p.type == 1) {
      type = p.type;
      v = p.v;
    } else {
      v += p.v;
    }
  }
};

// Light-edge の情報
template< typename Lazy >
struct LInfo {
  T min, max, sum, sz;

  T all_min, all_max, all_sum, all_sz;

  // 単位元(キーの値はアクセスしないので未初期化でもよい
  LInfo() : all_min(inf_max), all_max(inf_min), all_sum(0), all_sz(0) {}

  // 初期化
  LInfo(T min, T max, T sum, T sz) : min(min), max(max), sum(sum), sz(sz) {}

  // l, r は Splay-tree の子 (原理上、各ノード区別はない)
  void update(const LInfo &l, const LInfo &r) {
    all_min = std::min({l.all_min, min, r.all_min});
    all_max = std::max({l.all_max, max, r.all_max});
    all_sum = l.all_sum + sum + r.all_sum;
    all_sz = l.all_sz + sz + r.all_sz;
  }

  // light-edgeに対する遅延伝搬
  void propagate(const Lazy &p) {
    if(p.type == 0) {
      return;
    } else if(p.type == 1) { // change
      min = p.v;
      max = p.v;
      sum = p.v * sz;
      all_min = p.v;
      all_max = p.v;
      all_sum = p.v * all_sz;
    } else { // inc
      min += p.v;
      max += p.v;
      sum += p.v * sz;
      all_min += p.v;
      all_max += p.v;
      all_sum += p.v * all_sz;
    }
  }
};

// Heavy-edge の情報
template< typename LInfo, typename Lazy >
struct Info {
  T v;

  T path_min, path_max, path_sum, path_sz;
  T light_min, light_max, light_sum, light_sz;

  // 単位元(キーの値はアクセスしないので未初期化でもよい
  Info() : light_min(inf_max), light_max(inf_min), light_sum(0), light_sz(0),
           path_min(inf_max), path_max(inf_min), path_sum(0), path_sz(0) {}

  // 初期化
  Info(T v) : v(v) {}

  // 反転
  void toggle() {}

  // pが親, cがheavy-edgeで結ばれた子, lがそれ以外の子
  void update(const Info &p, const Info &c, const LInfo &l) {
    light_min = min({p.light_min, c.light_min, l.all_min});
    light_max = max({p.light_max, c.light_max, l.all_max});
    light_sum = p.light_sum + c.light_sum + l.all_sum;
    light_sz = p.light_sz + c.light_sz + l.all_sz;

    path_min = min({p.path_min, v, c.path_min});
    path_max = max({p.path_max, v, c.path_max});
    path_sum = p.path_sum + v + c.path_sum;
    path_sz = p.path_sz + 1 + c.path_sz;
  }

  // 親と light-edge で繋げる
  LInfo link() const {
    return LInfo(min(light_min, path_min), max(light_max, path_max), path_sum + light_sum, light_sz + path_sz);
  }

  // 遅延伝搬
  void propagate(const Lazy &p) {
    if(p.type == 0) {
      return;
    } else if(p.type == 1) { // change
      v = p.v;
      path_min = p.v;
      path_max = p.v;
      path_sum = p.v * path_sz;
    } else { // inc
      v += p.v;
      path_min += p.v;
      path_max += p.v;
      path_sum += p.v * path_sz;
    }
  }

  // light-edgeに対する遅延伝搬
  // pathとsubtreeの遅延伝搬が両方ある場合に実装する
  void propagate_light(const Lazy &p) {
    if(p.type == 0 or light_min == inf_max) {
      return;
    } else if(p.type == 1) { // change
      light_min = p.v;
      light_max = p.v;
      light_sum = p.v * light_sz;
    } else { // inc
      light_min += p.v;
      light_max += p.v;
      light_sum += p.v * light_sz;
    }
  }
};

using LCT = SuperLinkCutTree< Info, LInfo, Lazy >;
