// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450

#include "../../template/template.hpp"

#include "../../structure/develop/super-link-cut-tree.hpp"

using T = int64_t;

// 遅延伝搬をする作用素
struct Lazy {
  int v;

  // 単位元
  Lazy() : v{inf} {}

  // 初期化
  Lazy(int v) : v{v} {}

  void propagate(const Lazy &p) {
    if(p.v != inf) v = p.v;
  }
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
  T v;

  T dp, dp_p, dp_c, all;
  int sz;


  // 単位元(キーの値はアクセスしないので未初期化でもよい
  Info() : dp{-infll}, dp_p{-infll}, dp_c{-infll}, all{0}, sz{0} {}

  // 初期化
  Info(T v) : v{v} {}

  // 反転
  void toggle() { swap(dp_p, dp_c); }

  // pが親, cがheavy-edgeで結ばれた子, lがそれ以外の子
  void update(const Info &p, const Info &c, const LInfo &l) {
    all = p.all + v + c.all;
    sz = p.sz + 1 + c.sz;

    dp = max({p.dp, c.dp, max< T >(0, p.dp_c) + v + max< T >(0, c.dp_p)});
    dp_p = max(p.dp_p, p.all + v + max< T >(0, c.dp_p));
    dp_c = max(c.dp_c, c.all + v + max< T >(0, p.dp_c));
  }

  // 親と light-edge で繋げる
  LInfo link() const { return LInfo(); }

  // 遅延伝搬
  void propagate(const Lazy &p) {
    if(p.v != inf) {
      v = p.v;
      all = v * sz;
      dp = dp_c = dp_p = max(v, all);
    }
  }

  // light-edgeに対する遅延伝搬
  // 基本的にはpropagateのみ実装すれば十分
  // pathとsubtreeの遅延伝搬が両方ある場合を除く
  void propagate_light(const Lazy &p) {}
};

using LCT = SuperLinkCutTree< Info, LInfo, Lazy >;


int main() {
  int N, Q;
  cin >> N >> Q;
  LCT lct;
  vector< LCT::NP > vs(N);
  for(int i = 0; i < N; i++) {
    T x;
    cin >> x;
    vs[i] = lct.alloc(x);
  }
  for(int i = 1; i < N; i++) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    lct.evert(vs[a]);
    lct.link(vs[a], vs[b]);
  }
  while(Q--) {
    int t, a, b, c;
    cin >> t >> a >> b >> c;
    --a, --b;
    if(t == 2) {
      cout << lct.query_path(vs[a], vs[b]).dp << "\n";
    } else {
      lct.set_propagate_path(vs[a], vs[b], c);
    }
  }
}
