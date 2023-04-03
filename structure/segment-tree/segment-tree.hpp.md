---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-dsl-2-a.test.cpp
    title: test/verify/aoj-dsl-2-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yukicoder-650.test.cpp
    title: test/verify/yukicoder-650.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/segment-tree.md
    document_title: "Segment Tree(\u30BB\u30B0\u30E1\u30F3\u30C8\u6728)"
    links: []
  bundledCode: "#line 1 \"structure/segment-tree/segment-tree.hpp\"\n/**\n * @brief\
    \ Segment Tree(\u30BB\u30B0\u30E1\u30F3\u30C8\u6728)\n * @docs docs/segment-tree.md\n\
    \ */\ntemplate< typename T, typename F >\nstruct SegmentTree {\n  int n, sz;\n\
    \  vector< T > seg;\n\n  const F f;\n  const T ti;\n\n  SegmentTree() = default;\n\
    \n  explicit SegmentTree(int n, const F f, const T &ti) : n(n), f(f), ti(ti) {\n\
    \    sz = 1;\n    while(sz < n) sz <<= 1;\n    seg.assign(2 * sz, ti);\n  }\n\n\
    \  explicit SegmentTree(const vector< T > &v, const F f, const T &ti) :\n    \
    \  SegmentTree((int) v.size(), f, ti) {\n    build(v);\n  }\n\n  void build(const\
    \ vector< T > &v) {\n    assert(n == (int) v.size());\n    for(int k = 0; k <\
    \ n; k++) seg[k + sz] = v[k];\n    for(int k = sz - 1; k > 0; k--) {\n      seg[k]\
    \ = f(seg[2 * k + 0], seg[2 * k + 1]);\n    }\n  }\n\n  void set(int k, const\
    \ T &x) {\n    k += sz;\n    seg[k] = x;\n    while(k >>= 1) {\n      seg[k] =\
    \ f(seg[2 * k + 0], seg[2 * k + 1]);\n    }\n  }\n\n  T get(int k) const {\n \
    \   return seg[k + sz];\n  }\n\n  T operator[](const int &k) const {\n    return\
    \ get(k);\n  }\n\n  void apply(int k, const T &x) {\n    k += sz;\n    seg[k]\
    \ = f(seg[k], x);\n    while(k >>= 1) {\n      seg[k] = f(seg[2 * k + 0], seg[2\
    \ * k + 1]);\n    }\n  }\n\n  T prod(int l, int r) const {\n    T L = ti, R =\
    \ ti;\n    for(l += sz, r += sz; l < r; l >>= 1, r >>= 1) {\n      if(l & 1) L\
    \ = f(L, seg[l++]);\n      if(r & 1) R = f(seg[--r], R);\n    }\n    return f(L,\
    \ R);\n  }\n\n  T all_prod() const {\n    return seg[1];\n  }\n\n  template< typename\
    \ C >\n  int find_first(int l, const C &check) const {\n    if(l >= n) return\
    \ n;\n    l += sz;\n    T sum = ti;\n    do {\n      while((l & 1) == 0) l >>=\
    \ 1;\n      if(check(f(sum, seg[l]))) {\n        while(l < sz) {\n          l\
    \ <<= 1;\n          auto nxt = f(sum, seg[l]);\n          if(not check(nxt)) {\n\
    \            sum = nxt;\n            l++;\n          }\n        }\n        return\
    \ l + 1 - sz;\n      }\n      sum = f(sum, seg[l++]);\n    } while((l & -l) !=\
    \ l);\n    return n;\n  }\n\n  template< typename C >\n  int find_last(int r,\
    \ const C &check) const {\n    if(r <= 0) return -1;\n    r += sz;\n    T sum\
    \ = ti;\n    do {\n      r--;\n      while(r > 1 and (r & 1)) r >>= 1;\n     \
    \ if(check(f(seg[r], sum))) {\n        while(r < sz) {\n          r = (r << 1)\
    \ + 1;\n          auto nxt = f(seg[r], sum);\n          if(not check(nxt)) {\n\
    \            sum = nxt;\n            r--;\n          }\n        }\n        return\
    \ r - sz;\n      }\n      sum = f(seg[r], sum);\n    } while((r & -r) != r);\n\
    \    return -1;\n  }\n};\n\ntemplate< typename T, typename F >\nSegmentTree< T,\
    \ F > get_segment_tree(int N, const F &f, const T &ti) {\n  return SegmentTree{N,\
    \ f, ti};\n}\n\ntemplate< typename T, typename F >\nSegmentTree< T, F > get_segment_tree(const\
    \ vector< T > &v, const F &f, const T &ti) {\n  return SegmentTree{v, f, ti};\n\
    }\n"
  code: "/**\n * @brief Segment Tree(\u30BB\u30B0\u30E1\u30F3\u30C8\u6728)\n * @docs\
    \ docs/segment-tree.md\n */\ntemplate< typename T, typename F >\nstruct SegmentTree\
    \ {\n  int n, sz;\n  vector< T > seg;\n\n  const F f;\n  const T ti;\n\n  SegmentTree()\
    \ = default;\n\n  explicit SegmentTree(int n, const F f, const T &ti) : n(n),\
    \ f(f), ti(ti) {\n    sz = 1;\n    while(sz < n) sz <<= 1;\n    seg.assign(2 *\
    \ sz, ti);\n  }\n\n  explicit SegmentTree(const vector< T > &v, const F f, const\
    \ T &ti) :\n      SegmentTree((int) v.size(), f, ti) {\n    build(v);\n  }\n\n\
    \  void build(const vector< T > &v) {\n    assert(n == (int) v.size());\n    for(int\
    \ k = 0; k < n; k++) seg[k + sz] = v[k];\n    for(int k = sz - 1; k > 0; k--)\
    \ {\n      seg[k] = f(seg[2 * k + 0], seg[2 * k + 1]);\n    }\n  }\n\n  void set(int\
    \ k, const T &x) {\n    k += sz;\n    seg[k] = x;\n    while(k >>= 1) {\n    \
    \  seg[k] = f(seg[2 * k + 0], seg[2 * k + 1]);\n    }\n  }\n\n  T get(int k) const\
    \ {\n    return seg[k + sz];\n  }\n\n  T operator[](const int &k) const {\n  \
    \  return get(k);\n  }\n\n  void apply(int k, const T &x) {\n    k += sz;\n  \
    \  seg[k] = f(seg[k], x);\n    while(k >>= 1) {\n      seg[k] = f(seg[2 * k +\
    \ 0], seg[2 * k + 1]);\n    }\n  }\n\n  T prod(int l, int r) const {\n    T L\
    \ = ti, R = ti;\n    for(l += sz, r += sz; l < r; l >>= 1, r >>= 1) {\n      if(l\
    \ & 1) L = f(L, seg[l++]);\n      if(r & 1) R = f(seg[--r], R);\n    }\n    return\
    \ f(L, R);\n  }\n\n  T all_prod() const {\n    return seg[1];\n  }\n\n  template<\
    \ typename C >\n  int find_first(int l, const C &check) const {\n    if(l >= n)\
    \ return n;\n    l += sz;\n    T sum = ti;\n    do {\n      while((l & 1) == 0)\
    \ l >>= 1;\n      if(check(f(sum, seg[l]))) {\n        while(l < sz) {\n     \
    \     l <<= 1;\n          auto nxt = f(sum, seg[l]);\n          if(not check(nxt))\
    \ {\n            sum = nxt;\n            l++;\n          }\n        }\n      \
    \  return l + 1 - sz;\n      }\n      sum = f(sum, seg[l++]);\n    } while((l\
    \ & -l) != l);\n    return n;\n  }\n\n  template< typename C >\n  int find_last(int\
    \ r, const C &check) const {\n    if(r <= 0) return -1;\n    r += sz;\n    T sum\
    \ = ti;\n    do {\n      r--;\n      while(r > 1 and (r & 1)) r >>= 1;\n     \
    \ if(check(f(seg[r], sum))) {\n        while(r < sz) {\n          r = (r << 1)\
    \ + 1;\n          auto nxt = f(seg[r], sum);\n          if(not check(nxt)) {\n\
    \            sum = nxt;\n            r--;\n          }\n        }\n        return\
    \ r - sz;\n      }\n      sum = f(seg[r], sum);\n    } while((r & -r) != r);\n\
    \    return -1;\n  }\n};\n\ntemplate< typename T, typename F >\nSegmentTree< T,\
    \ F > get_segment_tree(int N, const F &f, const T &ti) {\n  return SegmentTree{N,\
    \ f, ti};\n}\n\ntemplate< typename T, typename F >\nSegmentTree< T, F > get_segment_tree(const\
    \ vector< T > &v, const F &f, const T &ti) {\n  return SegmentTree{v, f, ti};\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: structure/segment-tree/segment-tree.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yukicoder-650.test.cpp
  - test/verify/aoj-dsl-2-a.test.cpp
documentation_of: structure/segment-tree/segment-tree.hpp
layout: document
redirect_from:
- /library/structure/segment-tree/segment-tree.hpp
- /library/structure/segment-tree/segment-tree.hpp.html
title: "Segment Tree(\u30BB\u30B0\u30E1\u30F3\u30C8\u6728)"
---
## 概要

完全二分木である. モノイドについて区間に対する演算が $O(\log N)$ で処理できる.

モノイドは次の条件を満たす代数的構造である.

* 結合律を満たす. つまり $S$ の各元 $a, b, c$ に対して, $(a \cdot b) \cdot c = a \cdot (b \cdot c)$ が満たされる.
* 単位元をもつ. つまり $S$ の任意の元 $a$ をとってきたときに $a \cdot e = e \cdot a = a$ なる $e$ が存在する.

実装では木を 1-indexed の配列で表現している. ノード $k$ について, 親ノードは $\frac k 2$, 子ノードは $2k$, $2k+1$ である.

## 使い方

計算量のオーダーを表記していない関数は全て $O(\log n)$ で動作する.

* `SegmentTree(n, f, M1)`: サイズ `n` で初期化する. ここで `f` は2つの区間の要素をマージする二項演算, `M1` はモノイドの単位元である. $O(n)$
* `SegmentTree(v, f, M1)`: 配列 `v` で初期化する. `f` と `M1` は上と同様. $O(n)$
* `build(v)`: 配列 `v` で初期化する. $O(n)$
* `set(k, x)`: `k` 番目の要素を `x` に変更する. 
* `get(k)`: `k` 番目の要素を返す. $O(1)$
* `operator[k]`: `k` 番目の要素を返す. $O(1)$
* `apply(k, x)`: `k` 番目の要素をその要素と `x` を二項演算した値に変更する. 
* `prod(l, r)`: 区間 $[l, r)$ に対して二項演算した結果を返す.
* `all_prod()`: 全体を二項演算した結果を返す. $O(1)$
* `find_first(a, check)`: $[a, x)$ が `check` を満たす最初の要素位置 $x$ を返す. 存在しないとき $n$ を返す. $O(\log n)$
* `find_last(b, check)`: $[x, b)$ が `check` を満たす最後の要素位置 $x$ を返す. 存在しないとき $-1$ を返す. $(\log n)$

`auto seg = get_segment_tree(N, f, M1);` のようにすると `decltype(f)` を用いなくてすむ.
