---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: structure/others/permutation-tree.hpp
    title: "Permutation Tree(\u9806\u5217\u6728)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-2450.test.cpp
    title: test/verify/aoj-2450.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-range-affine-range-sum.test.cpp
    title: test/verify/yosupo-range-affine-range-sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yukicoder-1720.test.cpp
    title: test/verify/yukicoder-1720.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/lazy-segment-tree.md
    document_title: "Lazy-Segment-Tree(\u9045\u5EF6\u4F1D\u642C\u30BB\u30B0\u30E1\u30F3\
      \u30C8\u6728)"
    links: []
  bundledCode: "#line 1 \"structure/segment-tree/lazy-segment-tree.hpp\"\n/**\n *\
    \ @brief Lazy-Segment-Tree(\u9045\u5EF6\u4F1D\u642C\u30BB\u30B0\u30E1\u30F3\u30C8\
    \u6728)\n * @docs docs/lazy-segment-tree.md\n */\ntemplate< typename T, typename\
    \ E, typename F, typename G, typename H >\nstruct LazySegmentTree {\nprivate:\n\
    \  int n{}, sz{}, height{};\n  vector< T > data;\n  vector< E > lazy;\n  const\
    \ F f;\n  const G g;\n  const H h;\n  const T ti;\n  const E ei;\n\n  inline void\
    \ update(int k) {\n    data[k] = f(data[2 * k + 0], data[2 * k + 1]);\n  }\n\n\
    \  inline void all_apply(int k, const E &x) {\n    data[k] = g(data[k], x);\n\
    \    if(k < sz) lazy[k] = h(lazy[k], x);\n  }\n\n  inline void propagate(int k)\
    \ {\n    if(lazy[k] != ei) {\n      all_apply(2 * k + 0, lazy[k]);\n      all_apply(2\
    \ * k + 1, lazy[k]);\n      lazy[k] = ei;\n    }\n  }\n\npublic:\n  LazySegmentTree()\
    \ = default;\n\n  explicit LazySegmentTree(int n, const F f, const G g, const\
    \ H h,\n                           const T &ti, const E &ei)\n      : n(n), f(f),\
    \ g(g), h(h), ti(ti), ei(ei) {\n    sz = 1;\n    height = 0;\n    while(sz < n)\
    \ sz <<= 1, height++;\n    data.assign(2 * sz, ti);\n    lazy.assign(2 * sz, ei);\n\
    \  }\n\n  explicit LazySegmentTree(const vector< T > &v, const F f, const G g,\
    \ const H h,\n                           const T &ti, const E &ei)\n      : LazySegmentTree(v.size(),\
    \ f, g, h, ti, ei) {\n    build(v);\n  }\n\n  void build(const vector< T > &v)\
    \ {\n    assert(n == (int) v.size());\n    for(int k = 0; k < n; k++) data[k +\
    \ sz] = v[k];\n    for(int k = sz - 1; k > 0; k--) update(k);\n  }\n\n  void set(int\
    \ k, const T &x) {\n    k += sz;\n    for(int i = height; i > 0; i--) propagate(k\
    \ >> i);\n    data[k] = x;\n    for(int i = 1; i <= height; i++) update(k >> i);\n\
    \  }\n\n  T get(int k) {\n    k += sz;\n    for(int i = height; i > 0; i--) propagate(k\
    \ >> i);\n    return data[k];\n  }\n\n  T operator[](int k) {\n    return get(k);\n\
    \  }\n\n  T prod(int l, int r) {\n    if(l >= r) return ti;\n    l += sz;\n  \
    \  r += sz;\n    for(int i = height; i > 0; i--) {\n      if(((l >> i) << i) !=\
    \ l) propagate(l >> i);\n      if(((r >> i) << i) != r) propagate((r - 1) >> i);\n\
    \    }\n    T L = ti, R = ti;\n    for(; l < r; l >>= 1, r >>= 1) {\n      if(l\
    \ & 1) L = f(L, data[l++]);\n      if(r & 1) R = f(data[--r], R);\n    }\n   \
    \ return f(L, R);\n  }\n\n  T all_prod() const {\n    return data[1];\n  }\n\n\
    \  void apply(int k, const E &x) {\n    k += sz;\n    for(int i = height; i >\
    \ 0; i--) propagate(k >> i);\n    data[k] = g(data[k], x);\n    for(int i = 1;\
    \ i <= height; i++) update(k >> i);\n  }\n\n  void apply(int l, int r, const E\
    \ &x) {\n    if(l >= r) return;\n    l += sz;\n    r += sz;\n    for(int i = height;\
    \ i > 0; i--) {\n      if(((l >> i) << i) != l) propagate(l >> i);\n      if(((r\
    \ >> i) << i) != r) propagate((r - 1) >> i);\n    }\n    {\n      int l2 = l,\
    \ r2 = r;\n      for(; l < r; l >>= 1, r >>= 1) {\n        if(l & 1) all_apply(l++,\
    \ x);\n        if(r & 1) all_apply(--r, x);\n      }\n      l = l2, r = r2;\n\
    \    }\n    for(int i = 1; i <= height; i++) {\n      if(((l >> i) << i) != l)\
    \ update(l >> i);\n      if(((r >> i) << i) != r) update((r - 1) >> i);\n    }\n\
    \  }\n\n  template< typename C >\n  int find_first(int l, const C &check) {\n\
    \    if(l >= n) return n;\n    l += sz;\n    for(int i = height; i > 0; i--) propagate(l\
    \ >> i);\n    T sum = ti;\n    do {\n      while((l & 1) == 0) l >>= 1;\n    \
    \  if(check(f(sum, data[l]))) {\n        while(l < sz) {\n          propagate(l);\n\
    \          l <<= 1;\n          auto nxt = f(sum, data[l]);\n          if(not check(nxt))\
    \ {\n            sum = nxt;\n            l++;\n          }\n        }\n      \
    \  return l + 1 - sz;\n      }\n      sum = f(sum, data[l++]);\n    } while((l\
    \ & -l) != l);\n    return n;\n  }\n\n  template< typename C >\n  int find_last(int\
    \ r, const C &check) {\n    if(r <= 0) return -1;\n    r += sz;\n    for(int i\
    \ = height; i > 0; i--) propagate((r - 1) >> i);\n    T sum = ti;\n    do {\n\
    \      r--;\n      while(r > 1 and (r & 1)) r >>= 1;\n      if(check(f(data[r],\
    \ sum))) {\n        while(r < sz) {\n          propagate(r);\n          r = (r\
    \ << 1) + 1;\n          auto nxt = f(data[r], sum);\n          if(not check(nxt))\
    \ {\n            sum = nxt;\n            r--;\n          }\n        }\n      \
    \  return r - sz;\n      }\n      sum = f(data[r], sum);\n    } while((r & -r)\
    \ != r);\n    return -1;\n  }\n};\n\ntemplate< typename T, typename E, typename\
    \ F, typename G, typename H >\nLazySegmentTree< T, E, F, G, H > get_lazy_segment_tree\n\
    \    (int N, const F &f, const G &g, const H &h, const T &ti, const E &ei) {\n\
    \  return LazySegmentTree{N, f, g, h, ti, ei};\n}\n\ntemplate< typename T, typename\
    \ E, typename F, typename G, typename H >\nLazySegmentTree< T, E, F, G, H > get_lazy_segment_tree\n\
    \    (const vector< T > &v, const F &f, const G &g, const H &h, const T &ti, const\
    \ E &ei) {\n  return LazySegmentTree{v, f, g, h, ti, ei};\n}\n"
  code: "/**\n * @brief Lazy-Segment-Tree(\u9045\u5EF6\u4F1D\u642C\u30BB\u30B0\u30E1\
    \u30F3\u30C8\u6728)\n * @docs docs/lazy-segment-tree.md\n */\ntemplate< typename\
    \ T, typename E, typename F, typename G, typename H >\nstruct LazySegmentTree\
    \ {\nprivate:\n  int n{}, sz{}, height{};\n  vector< T > data;\n  vector< E >\
    \ lazy;\n  const F f;\n  const G g;\n  const H h;\n  const T ti;\n  const E ei;\n\
    \n  inline void update(int k) {\n    data[k] = f(data[2 * k + 0], data[2 * k +\
    \ 1]);\n  }\n\n  inline void all_apply(int k, const E &x) {\n    data[k] = g(data[k],\
    \ x);\n    if(k < sz) lazy[k] = h(lazy[k], x);\n  }\n\n  inline void propagate(int\
    \ k) {\n    if(lazy[k] != ei) {\n      all_apply(2 * k + 0, lazy[k]);\n      all_apply(2\
    \ * k + 1, lazy[k]);\n      lazy[k] = ei;\n    }\n  }\n\npublic:\n  LazySegmentTree()\
    \ = default;\n\n  explicit LazySegmentTree(int n, const F f, const G g, const\
    \ H h,\n                           const T &ti, const E &ei)\n      : n(n), f(f),\
    \ g(g), h(h), ti(ti), ei(ei) {\n    sz = 1;\n    height = 0;\n    while(sz < n)\
    \ sz <<= 1, height++;\n    data.assign(2 * sz, ti);\n    lazy.assign(2 * sz, ei);\n\
    \  }\n\n  explicit LazySegmentTree(const vector< T > &v, const F f, const G g,\
    \ const H h,\n                           const T &ti, const E &ei)\n      : LazySegmentTree(v.size(),\
    \ f, g, h, ti, ei) {\n    build(v);\n  }\n\n  void build(const vector< T > &v)\
    \ {\n    assert(n == (int) v.size());\n    for(int k = 0; k < n; k++) data[k +\
    \ sz] = v[k];\n    for(int k = sz - 1; k > 0; k--) update(k);\n  }\n\n  void set(int\
    \ k, const T &x) {\n    k += sz;\n    for(int i = height; i > 0; i--) propagate(k\
    \ >> i);\n    data[k] = x;\n    for(int i = 1; i <= height; i++) update(k >> i);\n\
    \  }\n\n  T get(int k) {\n    k += sz;\n    for(int i = height; i > 0; i--) propagate(k\
    \ >> i);\n    return data[k];\n  }\n\n  T operator[](int k) {\n    return get(k);\n\
    \  }\n\n  T prod(int l, int r) {\n    if(l >= r) return ti;\n    l += sz;\n  \
    \  r += sz;\n    for(int i = height; i > 0; i--) {\n      if(((l >> i) << i) !=\
    \ l) propagate(l >> i);\n      if(((r >> i) << i) != r) propagate((r - 1) >> i);\n\
    \    }\n    T L = ti, R = ti;\n    for(; l < r; l >>= 1, r >>= 1) {\n      if(l\
    \ & 1) L = f(L, data[l++]);\n      if(r & 1) R = f(data[--r], R);\n    }\n   \
    \ return f(L, R);\n  }\n\n  T all_prod() const {\n    return data[1];\n  }\n\n\
    \  void apply(int k, const E &x) {\n    k += sz;\n    for(int i = height; i >\
    \ 0; i--) propagate(k >> i);\n    data[k] = g(data[k], x);\n    for(int i = 1;\
    \ i <= height; i++) update(k >> i);\n  }\n\n  void apply(int l, int r, const E\
    \ &x) {\n    if(l >= r) return;\n    l += sz;\n    r += sz;\n    for(int i = height;\
    \ i > 0; i--) {\n      if(((l >> i) << i) != l) propagate(l >> i);\n      if(((r\
    \ >> i) << i) != r) propagate((r - 1) >> i);\n    }\n    {\n      int l2 = l,\
    \ r2 = r;\n      for(; l < r; l >>= 1, r >>= 1) {\n        if(l & 1) all_apply(l++,\
    \ x);\n        if(r & 1) all_apply(--r, x);\n      }\n      l = l2, r = r2;\n\
    \    }\n    for(int i = 1; i <= height; i++) {\n      if(((l >> i) << i) != l)\
    \ update(l >> i);\n      if(((r >> i) << i) != r) update((r - 1) >> i);\n    }\n\
    \  }\n\n  template< typename C >\n  int find_first(int l, const C &check) {\n\
    \    if(l >= n) return n;\n    l += sz;\n    for(int i = height; i > 0; i--) propagate(l\
    \ >> i);\n    T sum = ti;\n    do {\n      while((l & 1) == 0) l >>= 1;\n    \
    \  if(check(f(sum, data[l]))) {\n        while(l < sz) {\n          propagate(l);\n\
    \          l <<= 1;\n          auto nxt = f(sum, data[l]);\n          if(not check(nxt))\
    \ {\n            sum = nxt;\n            l++;\n          }\n        }\n      \
    \  return l + 1 - sz;\n      }\n      sum = f(sum, data[l++]);\n    } while((l\
    \ & -l) != l);\n    return n;\n  }\n\n  template< typename C >\n  int find_last(int\
    \ r, const C &check) {\n    if(r <= 0) return -1;\n    r += sz;\n    for(int i\
    \ = height; i > 0; i--) propagate((r - 1) >> i);\n    T sum = ti;\n    do {\n\
    \      r--;\n      while(r > 1 and (r & 1)) r >>= 1;\n      if(check(f(data[r],\
    \ sum))) {\n        while(r < sz) {\n          propagate(r);\n          r = (r\
    \ << 1) + 1;\n          auto nxt = f(data[r], sum);\n          if(not check(nxt))\
    \ {\n            sum = nxt;\n            r--;\n          }\n        }\n      \
    \  return r - sz;\n      }\n      sum = f(data[r], sum);\n    } while((r & -r)\
    \ != r);\n    return -1;\n  }\n};\n\ntemplate< typename T, typename E, typename\
    \ F, typename G, typename H >\nLazySegmentTree< T, E, F, G, H > get_lazy_segment_tree\n\
    \    (int N, const F &f, const G &g, const H &h, const T &ti, const E &ei) {\n\
    \  return LazySegmentTree{N, f, g, h, ti, ei};\n}\n\ntemplate< typename T, typename\
    \ E, typename F, typename G, typename H >\nLazySegmentTree< T, E, F, G, H > get_lazy_segment_tree\n\
    \    (const vector< T > &v, const F &f, const G &g, const H &h, const T &ti, const\
    \ E &ei) {\n  return LazySegmentTree{v, f, g, h, ti, ei};\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: structure/segment-tree/lazy-segment-tree.hpp
  requiredBy:
  - structure/others/permutation-tree.hpp
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/aoj-2450.test.cpp
  - test/verify/yukicoder-1720.test.cpp
  - test/verify/yosupo-range-affine-range-sum.test.cpp
documentation_of: structure/segment-tree/lazy-segment-tree.hpp
layout: document
redirect_from:
- /library/structure/segment-tree/lazy-segment-tree.hpp
- /library/structure/segment-tree/lazy-segment-tree.hpp.html
title: "Lazy-Segment-Tree(\u9045\u5EF6\u4F1D\u642C\u30BB\u30B0\u30E1\u30F3\u30C8\u6728\
  )"
---
## 概要

遅延伝搬を用いることで, 区間に対する更新が可能になる. コンストラクタに対し追加で作用素モノイドの情報も与える.

## 使い方

計算量のオーダーを表記していない関数は全て $O(\log n)$ で動作する.

* `LazySegmentTree(n, f, g, h, M1, OM0)`: サイズ `n` で初期化する. ここで `f` は2つの区間の要素をマージする二項演算, `g` は要素と作用素をマージする二項演算, `h` は作用素同士をマージする二項演算, `M1` はモノイドの単位元, `OM0` は作用素の単位元である. $O(n)$
* `LazySegmentTree(v, f, g, h, M1, OM0)`: 配列 `v` で初期化する. 第2引数以降は上と同様. $O(n)$
* `build(v)`: 配列 `v` で初期化する. $O(n)$
* `set(k, x)`: `k` 番目の要素を `x` に更新する.
* `get(k)`: `k` 番目の要素を返す.
* `operator[k]`: `k` 番目の要素を返す.
* `prod(l, r)`: 区間 $[l, r)$ に対して二項演算した結果を返す.
* `all_prod()`: 全体を二項演算した結果を返す. $O(1)$
* `apply(k, x)`: `k` 番目の要素に作用素 `x` を適用する.
* `apply(l, r, x)`: 区間 $[l, r)$ に対して作用素 `x` を適用する.
* `find_first(a, check)`: $[a,x)$ が `check` を満たす最初の要素位置 $x$ を返す. 存在しないとき $n$ を返す.
* `find_last(b, check)`: $[x,b)$ が `check` を満たす最後の要素位置 $x$ を返す. 存在しないとき $-1$ を返す.

`auto seg = get_lazy_segment_tree(N, f, g, h, M1, OM0);` のようにすると `decltype(f)` などを用いなくてすむ.
