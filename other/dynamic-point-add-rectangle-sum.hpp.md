---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other/static-point-add-rectangle-sum.hpp
    title: Static Point Add Rectangle Sum
  - icon: ':question:'
    path: structure/others/binary-indexed-tree.hpp
    title: Binary-Indexed-Tree(BIT)
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-point-add-rectangle-sum-3.test.cpp
    title: test/verify/yosupo-point-add-rectangle-sum-3.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Dynamic Point Add Rectangle Sum
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
    \    return ans;\n  }\n};\n#line 2 \"other/dynamic-point-add-rectangle-sum.hpp\"\
    \n\n/**\n * @brief Dynamic Point Add Rectangle Sum\n */\ntemplate< typename T,\
    \ typename C >\nstruct DynamicPointAddRectangleSum {\n  using StaticRectangleSumSolver\
    \ = StaticPointAddRectangleSum< T, C >;\n\n  static_assert(is_integral< T >::value,\
    \ \"template parameter T must be integral type\");\n\n  struct Point {\n    T\
    \ x, y;\n    C w;\n  };\n\n  struct Query {\n    T l, d, r, u;\n  };\n\n  vector<\
    \ variant< Point, Query > > queries;\n\n  DynamicPointAddRectangleSum() = default;\n\
    \n  DynamicPointAddRectangleSum(int q) {\n    queries.reserve(q);\n  }\n\n  void\
    \ add_point(T x, T y, C w) {\n    queries.emplace_back(Point{x, y, w});\n  }\n\
    \n  // tatal weight of [l, r) * [d, u) points\n  void add_query(T l, T d, T r,\
    \ T u) {\n    queries.emplace_back(Query{l, d, r, u});\n  }\n\n  vector< C > calculate_queries()\
    \ {\n    int q = (int) queries.size();\n    vector< int > rev(q);\n    int sz\
    \ = 0;\n    for(int i = 0; i < q; i++) {\n      if(holds_alternative< Query >(queries[i]))\
    \ {\n        rev[i] = sz++;\n      }\n    }\n    vector< C > ans(sz);\n    queue<\
    \ pair< int, int > > range;\n    range.emplace(0, q);\n    while(not range.empty())\
    \ {\n      auto[l, r] = range.front();\n      range.pop();\n      int m = (l +\
    \ r) >> 1;\n      StaticRectangleSumSolver solver;\n      for(int k = l; k < m;\
    \ k++) {\n        if(holds_alternative< Point >(queries[k])) {\n          auto\
    \ &point = get< Point >(queries[k]);\n          solver.add_point(point.x, point.y,\
    \ point.w);\n        }\n      }\n      for(int k = m; k < r; k++) {\n        if(holds_alternative<\
    \ Query >(queries[k])) {\n          auto &query = get< Query >(queries[k]);\n\
    \          solver.add_query(query.l, query.d, query.r, query.u);\n        }\n\
    \      }\n      auto sub = solver.calculate_queries();\n      for(int k = m, t\
    \ = 0; k < r; k++) {\n        if(holds_alternative< Query >(queries[k])) {\n \
    \         ans[rev[k]] += sub[t++];\n        }\n      }\n      if(l + 1 < m) range.emplace(l,\
    \ m);\n      if(m + 1 < r) range.emplace(m, r);\n    }\n    return ans;\n  }\n\
    };\n"
  code: "#include \"static-point-add-rectangle-sum.hpp\"\n\n/**\n * @brief Dynamic\
    \ Point Add Rectangle Sum\n */\ntemplate< typename T, typename C >\nstruct DynamicPointAddRectangleSum\
    \ {\n  using StaticRectangleSumSolver = StaticPointAddRectangleSum< T, C >;\n\n\
    \  static_assert(is_integral< T >::value, \"template parameter T must be integral\
    \ type\");\n\n  struct Point {\n    T x, y;\n    C w;\n  };\n\n  struct Query\
    \ {\n    T l, d, r, u;\n  };\n\n  vector< variant< Point, Query > > queries;\n\
    \n  DynamicPointAddRectangleSum() = default;\n\n  DynamicPointAddRectangleSum(int\
    \ q) {\n    queries.reserve(q);\n  }\n\n  void add_point(T x, T y, C w) {\n  \
    \  queries.emplace_back(Point{x, y, w});\n  }\n\n  // tatal weight of [l, r) *\
    \ [d, u) points\n  void add_query(T l, T d, T r, T u) {\n    queries.emplace_back(Query{l,\
    \ d, r, u});\n  }\n\n  vector< C > calculate_queries() {\n    int q = (int) queries.size();\n\
    \    vector< int > rev(q);\n    int sz = 0;\n    for(int i = 0; i < q; i++) {\n\
    \      if(holds_alternative< Query >(queries[i])) {\n        rev[i] = sz++;\n\
    \      }\n    }\n    vector< C > ans(sz);\n    queue< pair< int, int > > range;\n\
    \    range.emplace(0, q);\n    while(not range.empty()) {\n      auto[l, r] =\
    \ range.front();\n      range.pop();\n      int m = (l + r) >> 1;\n      StaticRectangleSumSolver\
    \ solver;\n      for(int k = l; k < m; k++) {\n        if(holds_alternative< Point\
    \ >(queries[k])) {\n          auto &point = get< Point >(queries[k]);\n      \
    \    solver.add_point(point.x, point.y, point.w);\n        }\n      }\n      for(int\
    \ k = m; k < r; k++) {\n        if(holds_alternative< Query >(queries[k])) {\n\
    \          auto &query = get< Query >(queries[k]);\n          solver.add_query(query.l,\
    \ query.d, query.r, query.u);\n        }\n      }\n      auto sub = solver.calculate_queries();\n\
    \      for(int k = m, t = 0; k < r; k++) {\n        if(holds_alternative< Query\
    \ >(queries[k])) {\n          ans[rev[k]] += sub[t++];\n        }\n      }\n \
    \     if(l + 1 < m) range.emplace(l, m);\n      if(m + 1 < r) range.emplace(m,\
    \ r);\n    }\n    return ans;\n  }\n};\n"
  dependsOn:
  - other/static-point-add-rectangle-sum.hpp
  - structure/others/binary-indexed-tree.hpp
  isVerificationFile: false
  path: other/dynamic-point-add-rectangle-sum.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-point-add-rectangle-sum-3.test.cpp
documentation_of: other/dynamic-point-add-rectangle-sum.hpp
layout: document
redirect_from:
- /library/other/dynamic-point-add-rectangle-sum.hpp
- /library/other/dynamic-point-add-rectangle-sum.hpp.html
title: Dynamic Point Add Rectangle Sum
---
