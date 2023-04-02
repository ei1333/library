---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-2725.test.cpp
    title: test/verify/aoj-2725.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-line-add-get-min.test.cpp
    title: test/verify/yosupo-line-add-get-min.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-segment-add-get-min.test.cpp
    title: test/verify/yosupo-segment-add-get-min.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/dynamic-li-chao-tree.md
    document_title: Dynamic-Li-Chao-Tree
    links: []
  bundledCode: "#line 1 \"structure/convex-hull-trick/dynamic-li-chao-tree.hpp\"\n\
    /**\n * @brief Dynamic-Li-Chao-Tree\n * @docs docs/dynamic-li-chao-tree.md\n*/\n\
    template< typename T, T x_low, T x_high, T id >\nstruct DynamicLiChaoTree {\n\n\
    \  struct Line {\n    T a, b;\n\n    Line(T a, T b) : a(a), b(b) {}\n\n    inline\
    \ T get(T x) const { return a * x + b; }\n  };\n\n  struct Node {\n    Line x;\n\
    \    Node *l, *r;\n\n    Node(const Line &x) : x{x}, l{nullptr}, r{nullptr} {}\n\
    \  };\n\n  Node *root;\n\n  DynamicLiChaoTree() : root{nullptr} {}\n\n  Node *add_line(Node\
    \ *t, Line &x, const T &l, const T &r, const T &x_l, const T &x_r) {\n    if(!t)\
    \ return new Node(x);\n\n    T t_l = t->x.get(l), t_r = t->x.get(r);\n\n    if(t_l\
    \ <= x_l && t_r <= x_r) {\n      return t;\n    } else if(t_l >= x_l && t_r >=\
    \ x_r) {\n      t->x = x;\n      return t;\n    } else {\n      T m = (l + r)\
    \ / 2;\n      if(m == r) --m;\n      T t_m = t->x.get(m), x_m = x.get(m);\n  \
    \    if(t_m > x_m) {\n        swap(t->x, x);\n        if(x_l >= t_l) t->l = add_line(t->l,\
    \ x, l, m, t_l, t_m);\n        else t->r = add_line(t->r, x, m + 1, r, t_m + x.a,\
    \ t_r);\n      } else {\n        if(t_l >= x_l) t->l = add_line(t->l, x, l, m,\
    \ x_l, x_m);\n        else t->r = add_line(t->r, x, m + 1, r, x_m + x.a, x_r);\n\
    \      }\n      return t;\n    }\n  }\n\n  void add_line(const T &a, const T &b)\
    \ {\n    Line x(a, b);\n    root = add_line(root, x, x_low, x_high, x.get(x_low),\
    \ x.get(x_high));\n  }\n\n  Node *add_segment(Node *t, Line &x, const T &a, const\
    \ T &b, const T &l, const T &r, const T &x_l, const T &x_r) {\n    if(r < a ||\
    \ b < l) return t;\n    if(a <= l && r <= b) {\n      Line y{x};\n      return\
    \ add_line(t, y, l, r, x_l, x_r);\n    }\n    if(t) {\n      T t_l = t->x.get(l),\
    \ t_r = t->x.get(r);\n      if(t_l <= x_l && t_r <= x_r) return t;\n    } else\
    \ {\n      t = new Node(Line(0, id));\n    }\n    T m = (l + r) / 2;\n    if(m\
    \ == r) --m;\n    T x_m = x.get(m);\n    t->l = add_segment(t->l, x, a, b, l,\
    \ m, x_l, x_m);\n    t->r = add_segment(t->r, x, a, b, m + 1, r, x_m + x.a, x_r);\n\
    \    return t;\n  }\n\n  void add_segment(const T &l, const T &r, const T &a,\
    \ const T &b) {\n    Line x(a, b);\n    root = add_segment(root, x, l, r - 1,\
    \ x_low, x_high, x.get(x_low), x.get(x_high));\n  }\n\n  T query(const Node *t,\
    \ const T &l, const T &r, const T &x) const {\n    if(!t) return id;\n    if(l\
    \ == r) return t->x.get(x);\n    T m = (l + r) / 2;\n    if(m == r) --m;\n   \
    \ if(x <= m) return min(t->x.get(x), query(t->l, l, m, x));\n    else return min(t->x.get(x),\
    \ query(t->r, m + 1, r, x));\n  }\n\n  T query(const T &x) const {\n    return\
    \ query(root, x_low, x_high, x);\n  }\n};\n"
  code: "/**\n * @brief Dynamic-Li-Chao-Tree\n * @docs docs/dynamic-li-chao-tree.md\n\
    */\ntemplate< typename T, T x_low, T x_high, T id >\nstruct DynamicLiChaoTree\
    \ {\n\n  struct Line {\n    T a, b;\n\n    Line(T a, T b) : a(a), b(b) {}\n\n\
    \    inline T get(T x) const { return a * x + b; }\n  };\n\n  struct Node {\n\
    \    Line x;\n    Node *l, *r;\n\n    Node(const Line &x) : x{x}, l{nullptr},\
    \ r{nullptr} {}\n  };\n\n  Node *root;\n\n  DynamicLiChaoTree() : root{nullptr}\
    \ {}\n\n  Node *add_line(Node *t, Line &x, const T &l, const T &r, const T &x_l,\
    \ const T &x_r) {\n    if(!t) return new Node(x);\n\n    T t_l = t->x.get(l),\
    \ t_r = t->x.get(r);\n\n    if(t_l <= x_l && t_r <= x_r) {\n      return t;\n\
    \    } else if(t_l >= x_l && t_r >= x_r) {\n      t->x = x;\n      return t;\n\
    \    } else {\n      T m = (l + r) / 2;\n      if(m == r) --m;\n      T t_m =\
    \ t->x.get(m), x_m = x.get(m);\n      if(t_m > x_m) {\n        swap(t->x, x);\n\
    \        if(x_l >= t_l) t->l = add_line(t->l, x, l, m, t_l, t_m);\n        else\
    \ t->r = add_line(t->r, x, m + 1, r, t_m + x.a, t_r);\n      } else {\n      \
    \  if(t_l >= x_l) t->l = add_line(t->l, x, l, m, x_l, x_m);\n        else t->r\
    \ = add_line(t->r, x, m + 1, r, x_m + x.a, x_r);\n      }\n      return t;\n \
    \   }\n  }\n\n  void add_line(const T &a, const T &b) {\n    Line x(a, b);\n \
    \   root = add_line(root, x, x_low, x_high, x.get(x_low), x.get(x_high));\n  }\n\
    \n  Node *add_segment(Node *t, Line &x, const T &a, const T &b, const T &l, const\
    \ T &r, const T &x_l, const T &x_r) {\n    if(r < a || b < l) return t;\n    if(a\
    \ <= l && r <= b) {\n      Line y{x};\n      return add_line(t, y, l, r, x_l,\
    \ x_r);\n    }\n    if(t) {\n      T t_l = t->x.get(l), t_r = t->x.get(r);\n \
    \     if(t_l <= x_l && t_r <= x_r) return t;\n    } else {\n      t = new Node(Line(0,\
    \ id));\n    }\n    T m = (l + r) / 2;\n    if(m == r) --m;\n    T x_m = x.get(m);\n\
    \    t->l = add_segment(t->l, x, a, b, l, m, x_l, x_m);\n    t->r = add_segment(t->r,\
    \ x, a, b, m + 1, r, x_m + x.a, x_r);\n    return t;\n  }\n\n  void add_segment(const\
    \ T &l, const T &r, const T &a, const T &b) {\n    Line x(a, b);\n    root = add_segment(root,\
    \ x, l, r - 1, x_low, x_high, x.get(x_low), x.get(x_high));\n  }\n\n  T query(const\
    \ Node *t, const T &l, const T &r, const T &x) const {\n    if(!t) return id;\n\
    \    if(l == r) return t->x.get(x);\n    T m = (l + r) / 2;\n    if(m == r) --m;\n\
    \    if(x <= m) return min(t->x.get(x), query(t->l, l, m, x));\n    else return\
    \ min(t->x.get(x), query(t->r, m + 1, r, x));\n  }\n\n  T query(const T &x) const\
    \ {\n    return query(root, x_low, x_high, x);\n  }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: structure/convex-hull-trick/dynamic-li-chao-tree.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-line-add-get-min.test.cpp
  - test/verify/aoj-2725.test.cpp
  - test/verify/yosupo-segment-add-get-min.test.cpp
documentation_of: structure/convex-hull-trick/dynamic-li-chao-tree.hpp
layout: document
redirect_from:
- /library/structure/convex-hull-trick/dynamic-li-chao-tree.hpp
- /library/structure/convex-hull-trick/dynamic-li-chao-tree.hpp.html
title: Dynamic-Li-Chao-Tree
---
## 概要

直線 $ax+b$ の追加クエリと, ある点 $x$ での最小値クエリを効率的に処理するデータ構造.

セグメント木の各ノードにその区間で最小の直線を載せるイメージ.

直線の追加クエリでは, そのノード $[l, r)$ の既存の直線と比較する. 交差しないとき上側の直線を捨て, 交差するときは $x$ を区間の中心 $\frac {l + r} {2}$ としたときの値の大小関係を比較する. 小さい方をそのノードの直線とし, 大きい方は子に再帰的に追加する.

点 $x$ での最小値クエリでは, $x$ を含むノードが $O(\log n)$ 個なので, それらを見ればよい.

静的な Li-Chao-Tree と動的な Li-Chao-Tree の速度差は(感覚的には)小さいため, 基本的には最小値クエリの先読みが不要な動的な方がおすすめ.

## 使い方

`x_low` には `query()` で与える $x$ の最小値, `x_high` には $x$ の最大値, `id` は単位元(十分大きい値) を指定する. すべての直線について `x_low`, `x_high` がオーバーフローしないとき意図した動作をする.

最大値クエリは最小値クエリに帰着できて, `add_line(-a, -b)`, `-query(x)` とすればよい.


* `add_line(a, b)`: 直線 $ax + b$ を追加する.
* `add_segment(l, r, a, b)`: 区間 $[l, r)$ に線分 $ax + b$ を追加する.
* `query(x)`: $ax + b$ の最小値を求める.

## 計算量

* `add_line(), query()`: $O(\log V)$
* `add_segment()`: $O(\log^2 V)$

$V$ は $x$ が動く範囲.
