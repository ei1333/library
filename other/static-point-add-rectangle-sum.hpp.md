---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: structure/others/binary-indexed-tree.hpp
    title: Binary-Indexed-Tree(BIT)
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: other/dynamic-point-add-rectangle-sum.hpp
    title: Dynamic Point Add Rectangle Sum
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-point-add-rectangle-sum-3.test.cpp
    title: test/verify/yosupo-point-add-rectangle-sum-3.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-rectangle-sum-2.test.cpp
    title: test/verify/yosupo-rectangle-sum-2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Static Point Add Rectangle Sum
    links: []
  bundledCode: "#line 1 \"structure/others/binary-indexed-tree.hpp\"\n/**\n * @brief\
    \ Binary-Indexed-Tree(BIT)\n * @docs docs/binary-indexed-tree.md\n */\ntemplate<\
    \ typename T >\nstruct BinaryIndexedTree {\nprivate:\n  int n;\n  vector< T >\
    \ data;\n\npublic:\n  BinaryIndexedTree() = default;\n\n  explicit BinaryIndexedTree(int\
    \ n) : n(n) {\n    data.assign(n + 1, T());\n  }\n\n  explicit BinaryIndexedTree(const\
    \ vector< T > &v) :\n      BinaryIndexedTree((int) v.size()) {\n    build(v);\n\
    \  }\n\n  void build(const vector< T > &v) {\n    assert(n == (int) v.size());\n\
    \    for(int i = 1; i <= n; i++) data[i] = v[i - 1];\n    for(int i = 1; i <=\
    \ n; i++) {\n      int j = i + (i & -i);\n      if(j <= n) data[j] += data[i];\n\
    \    }\n  }\n\n  void apply(int k, const T &x) {\n    for(++k; k <= n; k += k\
    \ & -k) data[k] += x;\n  }\n\n  T prod(int r) const {\n    T ret = T();\n    for(;\
    \ r > 0; r -= r & -r) ret += data[r];\n    return ret;\n  }\n\n  T prod(int l,\
    \ int r) const {\n    return prod(r) - prod(l);\n  }\n\n  int lower_bound(T x)\
    \ const {\n    int i = 0;\n    for(int k = 1 << (__lg(n) + 1); k > 0; k >>= 1)\
    \ {\n      if(i + k <= n && data[i + k] < x) {\n        x -= data[i + k];\n  \
    \      i += k;\n      }\n    }\n    return i;\n  }\n\n  int upper_bound(T x) const\
    \ {\n    int i = 0;\n    for(int k = 1 << (__lg(n) + 1); k > 0; k >>= 1) {\n \
    \     if(i + k <= n && data[i + k] <= x) {\n        x -= data[i + k];\n      \
    \  i += k;\n      }\n    }\n    return i;\n  }\n};\n#line 2 \"other/static-point-add-rectangle-sum.hpp\"\
    \n\n/**\n * @brief Static Point Add Rectangle Sum\n */\ntemplate< typename T,\
    \ typename C >\nstruct StaticPointAddRectangleSum {\n  using BIT = BinaryIndexedTree<\
    \ C >;\n\n  static_assert(is_integral< T >::value, \"template parameter T must\
    \ be integral type\");\n\n  struct Point {\n    T x, y;\n    C w;\n  };\n\n  struct\
    \ Query {\n    T l, d, r, u;\n  };\n\n  vector< Point > points;\n  vector< Query\
    \ > queries;\n\n  StaticPointAddRectangleSum() = default;\n\n  StaticPointAddRectangleSum(int\
    \ n, int q) {\n    points.reserve(n);\n    queries.reserve(q);\n  }\n\n  void\
    \ add_point(T x, T y, C w) {\n    points.emplace_back(Point{x, y, w});\n  }\n\n\
    \  // tatal weight of [l, r) * [d, u) points\n  void add_query(T l, T d, T r,\
    \ T u) {\n    queries.emplace_back(Query{l, d, r, u});\n  }\n\n  vector< C > calculate_queries()\
    \ {\n    int n = (int) points.size();\n    int q = (int) queries.size();\n   \
    \ vector< C > ans(q);\n    if(points.empty() or queries.empty()) {\n      return\
    \ ans;\n    }\n    sort(points.begin(), points.end(), [](const Point &a, const\
    \ Point &b) {\n      return a.y < b.y;\n    });\n    vector< T > ys;\n    ys.reserve(n);\n\
    \    for(Point &p: points) {\n      if(ys.empty() or ys.back() != p.y) ys.emplace_back(p.y);\n\
    \      p.y = (int) ys.size() - 1;\n    }\n    ys.shrink_to_fit();\n\n    struct\
    \ Q {\n      T x;\n      int d, u;\n      bool type;\n      int idx;\n    };\n\
    \    vector< Q > qs;\n    qs.reserve(q + q);\n    for(int i = 0; i < q; i++) {\n\
    \      auto &query = queries[i];\n      int d = lower_bound(ys.begin(), ys.end(),\
    \ query.d) - ys.begin();\n      int u = lower_bound(ys.begin(), ys.end(), query.u)\
    \ - ys.begin();\n      qs.emplace_back(Q{query.l, d, u, false, i});\n      qs.emplace_back(Q{query.r,\
    \ d, u, true, i});\n    }\n    sort(points.begin(), points.end(), [](const Point\
    \ &a, const Point &b) {\n      return a.x < b.x;\n    });\n    sort(qs.begin(),\
    \ qs.end(), [](const Q &a, const Q &b) {\n      return a.x < b.x;\n    });\n \
    \   int j = 0;\n    BIT bit(ys.size());\n    for(auto &query: qs) {\n      while(j\
    \ < n and points[j].x < query.x) {\n        bit.apply(points[j].y, points[j].w);\n\
    \        ++j;\n      }\n      if(query.type) ans[query.idx] += bit.prod(query.d,\
    \ query.u);\n      else ans[query.idx] -= bit.prod(query.d, query.u);\n    }\n\
    \    return ans;\n  }\n};\n"
  code: "#include \"../structure/others/binary-indexed-tree.hpp\"\n\n/**\n * @brief\
    \ Static Point Add Rectangle Sum\n */\ntemplate< typename T, typename C >\nstruct\
    \ StaticPointAddRectangleSum {\n  using BIT = BinaryIndexedTree< C >;\n\n  static_assert(is_integral<\
    \ T >::value, \"template parameter T must be integral type\");\n\n  struct Point\
    \ {\n    T x, y;\n    C w;\n  };\n\n  struct Query {\n    T l, d, r, u;\n  };\n\
    \n  vector< Point > points;\n  vector< Query > queries;\n\n  StaticPointAddRectangleSum()\
    \ = default;\n\n  StaticPointAddRectangleSum(int n, int q) {\n    points.reserve(n);\n\
    \    queries.reserve(q);\n  }\n\n  void add_point(T x, T y, C w) {\n    points.emplace_back(Point{x,\
    \ y, w});\n  }\n\n  // tatal weight of [l, r) * [d, u) points\n  void add_query(T\
    \ l, T d, T r, T u) {\n    queries.emplace_back(Query{l, d, r, u});\n  }\n\n \
    \ vector< C > calculate_queries() {\n    int n = (int) points.size();\n    int\
    \ q = (int) queries.size();\n    vector< C > ans(q);\n    if(points.empty() or\
    \ queries.empty()) {\n      return ans;\n    }\n    sort(points.begin(), points.end(),\
    \ [](const Point &a, const Point &b) {\n      return a.y < b.y;\n    });\n   \
    \ vector< T > ys;\n    ys.reserve(n);\n    for(Point &p: points) {\n      if(ys.empty()\
    \ or ys.back() != p.y) ys.emplace_back(p.y);\n      p.y = (int) ys.size() - 1;\n\
    \    }\n    ys.shrink_to_fit();\n\n    struct Q {\n      T x;\n      int d, u;\n\
    \      bool type;\n      int idx;\n    };\n    vector< Q > qs;\n    qs.reserve(q\
    \ + q);\n    for(int i = 0; i < q; i++) {\n      auto &query = queries[i];\n \
    \     int d = lower_bound(ys.begin(), ys.end(), query.d) - ys.begin();\n     \
    \ int u = lower_bound(ys.begin(), ys.end(), query.u) - ys.begin();\n      qs.emplace_back(Q{query.l,\
    \ d, u, false, i});\n      qs.emplace_back(Q{query.r, d, u, true, i});\n    }\n\
    \    sort(points.begin(), points.end(), [](const Point &a, const Point &b) {\n\
    \      return a.x < b.x;\n    });\n    sort(qs.begin(), qs.end(), [](const Q &a,\
    \ const Q &b) {\n      return a.x < b.x;\n    });\n    int j = 0;\n    BIT bit(ys.size());\n\
    \    for(auto &query: qs) {\n      while(j < n and points[j].x < query.x) {\n\
    \        bit.apply(points[j].y, points[j].w);\n        ++j;\n      }\n      if(query.type)\
    \ ans[query.idx] += bit.prod(query.d, query.u);\n      else ans[query.idx] -=\
    \ bit.prod(query.d, query.u);\n    }\n    return ans;\n  }\n};\n"
  dependsOn:
  - structure/others/binary-indexed-tree.hpp
  isVerificationFile: false
  path: other/static-point-add-rectangle-sum.hpp
  requiredBy:
  - other/dynamic-point-add-rectangle-sum.hpp
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-rectangle-sum-2.test.cpp
  - test/verify/yosupo-point-add-rectangle-sum-3.test.cpp
documentation_of: other/static-point-add-rectangle-sum.hpp
layout: document
redirect_from:
- /library/other/static-point-add-rectangle-sum.hpp
- /library/other/static-point-add-rectangle-sum.hpp.html
title: Static Point Add Rectangle Sum
---
