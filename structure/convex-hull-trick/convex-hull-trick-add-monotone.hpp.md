---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-line-add-get-min-2.test.cpp
    title: test/verify/yosupo-line-add-get-min-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yukicoder-952.test.cpp
    title: test/verify/yukicoder-952.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/convex-hull-trick-add-monotone.md
    document_title: Convex Hull Trick Add Monotone
    links: []
  bundledCode: "#line 1 \"structure/convex-hull-trick/convex-hull-trick-add-monotone.hpp\"\
    \n/**\n * @brief Convex Hull Trick Add Monotone\n * @docs docs/convex-hull-trick-add-monotone.md\n\
    */\ntemplate< typename T, bool isMin >\nstruct ConvexHullTrickAddMonotone {\n\
    #define F first\n#define S second\n  using P = pair< T, T >;\n  deque< P > H;\n\
    \n  ConvexHullTrickAddMonotone() = default;\n\n  bool empty() const { return H.empty();\
    \ }\n\n  void clear() { H.clear(); }\n\n  inline int sgn(T x) { return x == 0\
    \ ? 0 : (x < 0 ? -1 : 1); }\n\n  inline bool check(const P &a, const P &b, const\
    \ P &c) {\n    if(b.S == a.S || c.S == b.S)\n      return sgn(b.F - a.F) * sgn(c.S\
    \ - b.S) >= sgn(c.F - b.F) * sgn(b.S - a.S);\n    //return (b.F-a.F)*(c.S-b.S)\
    \ >= (b.S-a.S)*(c.F-b.F);\n    if(is_integral< T >::value) {\n      return (b.S\
    \ - a.S) / (a.F - b.F) >= (c.S - b.S) / (b.F - c.F);\n    } else {\n      return\n\
    \          (b.F - a.F) * sgn(c.S - b.S) / abs(b.S - a.S) >=\n          (c.F -\
    \ b.F) * sgn(b.S - a.S) / abs(c.S - b.S);\n    }\n  }\n\n  void add(T a, T b)\
    \ {\n    if(!isMin) a *= -1, b *= -1;\n    P line(a, b);\n    if(empty()) {\n\
    \      H.emplace_front(line);\n      return;\n    }\n    if(H.front().F <= a)\
    \ {\n      if(H.front().F == a) {\n        if(H.front().S <= b) return;\n    \
    \    H.pop_front();\n      }\n      while(H.size() >= 2 && check(line, H.front(),\
    \ H[1])) H.pop_front();\n      H.emplace_front(line);\n    } else {\n      assert(a\
    \ <= H.back().F);\n      if(H.back().F == a) {\n        if(H.back().S <= b) return;\n\
    \        H.pop_back();\n      }\n      while(H.size() >= 2 && check(H[H.size()\
    \ - 2], H.back(), line)) H.pop_back();\n      H.emplace_back(line);\n    }\n \
    \ }\n\n  inline T get_y(const P &a, const T &x) {\n    return a.F * x + a.S;\n\
    \  }\n\n  T query(T x) {\n    assert(!empty());\n    int l = -1, r = H.size()\
    \ - 1;\n    while(l + 1 < r) {\n      int m = (l + r) >> 1;\n      if(get_y(H[m],\
    \ x) >= get_y(H[m + 1], x)) l = m;\n      else r = m;\n    }\n    if(isMin) return\
    \ get_y(H[r], x);\n    return -get_y(H[r], x);\n  }\n\n  T query_monotone_inc(T\
    \ x) {\n    assert(!empty());\n    while(H.size() >= 2 && get_y(H.front(), x)\
    \ >= get_y(H[1], x)) H.pop_front();\n    if(isMin) return get_y(H.front(), x);\n\
    \    return -get_y(H.front(), x);\n  }\n\n  T query_monotone_dec(T x) {\n    assert(!empty());\n\
    \    while(H.size() >= 2 && get_y(H.back(), x) >= get_y(H[H.size() - 2], x)) H.pop_back();\n\
    \    if(isMin) return get_y(H.back(), x);\n    return -get_y(H.back(), x);\n \
    \ }\n\n#undef F\n#undef S\n};\n"
  code: "/**\n * @brief Convex Hull Trick Add Monotone\n * @docs docs/convex-hull-trick-add-monotone.md\n\
    */\ntemplate< typename T, bool isMin >\nstruct ConvexHullTrickAddMonotone {\n\
    #define F first\n#define S second\n  using P = pair< T, T >;\n  deque< P > H;\n\
    \n  ConvexHullTrickAddMonotone() = default;\n\n  bool empty() const { return H.empty();\
    \ }\n\n  void clear() { H.clear(); }\n\n  inline int sgn(T x) { return x == 0\
    \ ? 0 : (x < 0 ? -1 : 1); }\n\n  inline bool check(const P &a, const P &b, const\
    \ P &c) {\n    if(b.S == a.S || c.S == b.S)\n      return sgn(b.F - a.F) * sgn(c.S\
    \ - b.S) >= sgn(c.F - b.F) * sgn(b.S - a.S);\n    //return (b.F-a.F)*(c.S-b.S)\
    \ >= (b.S-a.S)*(c.F-b.F);\n    if(is_integral< T >::value) {\n      return (b.S\
    \ - a.S) / (a.F - b.F) >= (c.S - b.S) / (b.F - c.F);\n    } else {\n      return\n\
    \          (b.F - a.F) * sgn(c.S - b.S) / abs(b.S - a.S) >=\n          (c.F -\
    \ b.F) * sgn(b.S - a.S) / abs(c.S - b.S);\n    }\n  }\n\n  void add(T a, T b)\
    \ {\n    if(!isMin) a *= -1, b *= -1;\n    P line(a, b);\n    if(empty()) {\n\
    \      H.emplace_front(line);\n      return;\n    }\n    if(H.front().F <= a)\
    \ {\n      if(H.front().F == a) {\n        if(H.front().S <= b) return;\n    \
    \    H.pop_front();\n      }\n      while(H.size() >= 2 && check(line, H.front(),\
    \ H[1])) H.pop_front();\n      H.emplace_front(line);\n    } else {\n      assert(a\
    \ <= H.back().F);\n      if(H.back().F == a) {\n        if(H.back().S <= b) return;\n\
    \        H.pop_back();\n      }\n      while(H.size() >= 2 && check(H[H.size()\
    \ - 2], H.back(), line)) H.pop_back();\n      H.emplace_back(line);\n    }\n \
    \ }\n\n  inline T get_y(const P &a, const T &x) {\n    return a.F * x + a.S;\n\
    \  }\n\n  T query(T x) {\n    assert(!empty());\n    int l = -1, r = H.size()\
    \ - 1;\n    while(l + 1 < r) {\n      int m = (l + r) >> 1;\n      if(get_y(H[m],\
    \ x) >= get_y(H[m + 1], x)) l = m;\n      else r = m;\n    }\n    if(isMin) return\
    \ get_y(H[r], x);\n    return -get_y(H[r], x);\n  }\n\n  T query_monotone_inc(T\
    \ x) {\n    assert(!empty());\n    while(H.size() >= 2 && get_y(H.front(), x)\
    \ >= get_y(H[1], x)) H.pop_front();\n    if(isMin) return get_y(H.front(), x);\n\
    \    return -get_y(H.front(), x);\n  }\n\n  T query_monotone_dec(T x) {\n    assert(!empty());\n\
    \    while(H.size() >= 2 && get_y(H.back(), x) >= get_y(H[H.size() - 2], x)) H.pop_back();\n\
    \    if(isMin) return get_y(H.back(), x);\n    return -get_y(H.back(), x);\n \
    \ }\n\n#undef F\n#undef S\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: structure/convex-hull-trick/convex-hull-trick-add-monotone.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yukicoder-952.test.cpp
  - test/verify/yosupo-line-add-get-min-2.test.cpp
documentation_of: structure/convex-hull-trick/convex-hull-trick-add-monotone.hpp
layout: document
redirect_from:
- /library/structure/convex-hull-trick/convex-hull-trick-add-monotone.hpp
- /library/structure/convex-hull-trick/convex-hull-trick-add-monotone.hpp.html
title: Convex Hull Trick Add Monotone
---
## 概要

直線 $ax+b$ の追加クエリ(ただし $a$ は単調増加または単調減少) と, ある点 $x$ での最小値クエリを効率的に処理する.

追加クエリは $a$ の単調性を考えながら, 上手く stack で管理することで効率的に処理できる(凸包を求めるアルゴリズムと似ている).

最小値クエリは $x$ が単調増加または単調減少のとき stack を端からみることで全体で $O(q + n)$, 単調性がない場合も二分探索することでクエリあたり $(\log n)$ で求められる.

## 使い方

`is_Min` を `true` にすると最小値, `false` にすると最大値を求める.

* `add(a, b)`: 直線 $ax + b$ を追加する. ただし $a$ は広義単調増加または広義単調減少.
* `query(x)`: $ax + b$ の最小値を求める.
* `query_monotone_inc(x)`: $ax + b$ の最小値を求める. ただし $x$ は広義単調増加.
* `query_monotone_dec(x)`: $ax + b$ の最小値を求める. ただし $x$ は広義単調減少.

## 計算量

* `add()`: 全体で $O(n)$
* `query()`: クエリあたり $O(\log n)$
* `query_monotone_inc(x)`, `query_monotone_dec(x)`: 全体で $O(n + q)$

$n$ は追加する直線の個数, $q$ はクエリ数. 
