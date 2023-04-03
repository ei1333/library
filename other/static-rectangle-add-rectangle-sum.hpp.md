---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: structure/others/binary-indexed-tree.hpp
    title: Binary-Indexed-Tree(BIT)
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Static Rectangle Add Rectangle Sum
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
    \  i += k;\n      }\n    }\n    return i;\n  }\n};\n#line 2 \"other/static-rectangle-add-rectangle-sum.hpp\"\
    \n\n/**\n * @brief Static Rectangle Add Rectangle Sum\n */\ntemplate< typename\
    \ T, typename C >\nstruct StaticRectangleAddRectangleSum {\n  struct Hikari :\
    \ array< C, 4 > {\n    using A = array< C, 4 >;\n\n    Hikari &operator+=(const\
    \ Hikari &p) {\n      for(int i = 0; i < 4; i++) {\n        this->at(i) += p.at(i);\n\
    \      }\n      return *this;\n    }\n  };\n\n  using BIT = BinaryIndexedTree<\
    \ Hikari >;\n\n  static_assert(is_integral< T >::value, \"template parameter T\
    \ must be integral type\");\n\n  struct Rectangle {\n    T l, d, r, u;\n    C\
    \ w;\n  };\n\n  struct Query {\n    T l, d, r, u;\n  };\n\n  vector< Rectangle\
    \ > rectangles;\n  vector< Query > queries;\n\n  StaticRectangleAddRectangleSum()\
    \ = default;\n\n  StaticRectangleAddRectangleSum(int n, int q) {\n    rectangles.reserve(n);\n\
    \    queries.reserve(q);\n  }\n\n  void add_rectangle(T l, T d, T r, T u, C w)\
    \ {\n    rectangles.emplace_back(Rectangle{l, d, r, u, w});\n  }\n\n  // total\
    \ weight of [l, r) * [d, u) points\n  void add_query(T l, T d, T r, T u) {\n \
    \   queries.emplace_back(Query{l, d, r, u});\n  }\n\n  vector< C > calculate_queries()\
    \ {\n    int n = (int) rectangles.size();\n    int q = (int) queries.size();\n\
    \    vector< C > ans(q);\n    if(rectangles.empty() or queries.empty()) {\n  \
    \    return ans;\n    }\n    vector< T > ys;\n    ys.reserve(n + n);\n    for(Rectangle\
    \ &p: rectangles) {\n      ys.emplace_back(p.d);\n      ys.emplace_back(p.u);\n\
    \    }\n    sort(ys.begin(), ys.end());\n    ys.erase(unique(ys.begin(), ys.end()),\
    \ ys.end());\n\n    struct Q {\n      T x;\n      int d, u;\n      bool type;\n\
    \      int idx;\n    };\n    vector< Q > rs, qs;\n    rs.reserve(n + n);\n   \
    \ qs.reserve(q + q);\n    for(int i = 0; i < n; i++) {\n      auto &p = rectangles[i];\n\
    \      int d = lower_bound(ys.begin(), ys.end(), p.d) - ys.begin();\n      int\
    \ u = lower_bound(ys.begin(), ys.end(), p.u) - ys.begin();\n      rs.emplace_back(Q{p.l,\
    \ d, u, false, i});\n      rs.emplace_back(Q{p.r, d, u, true, i});\n    }\n  \
    \  for(int i = 0; i < q; i++) {\n      auto &p = queries[i];\n      int d = lower_bound(ys.begin(),\
    \ ys.end(), p.d) - ys.begin();\n      int u = lower_bound(ys.begin(), ys.end(),\
    \ p.u) - ys.begin();\n      qs.emplace_back(Q{p.l, d, u, false, i});\n      qs.emplace_back(Q{p.r,\
    \ d, u, true, i});\n    }\n    sort(rs.begin(), rs.end(), [](const Q &a, const\
    \ Q &b) {\n      return a.x < b.x;\n    });\n    sort(qs.begin(), qs.end(), [](const\
    \ Q &a, const Q &b) {\n      return a.x < b.x;\n    });\n    int j = 0;\n    BIT\
    \ bit(ys.size());\n    for(auto &query: qs) {\n      while(j < n and rs[j].x <\
    \ query.x) {\n        auto &p = rectangles[j];\n        if(rs[j].type) {\n   \
    \       bit.apply(rs[j].d, {-p.w * p.r * p.d, -p.w, p.d * p.w, p.r * p.w});\n\
    \          bit.apply(rs[j].u, {p.w * p.r * p.u, p.w, -p.u * p.w, -p.r * p.w});\n\
    \        } else {\n          bit.apply(rs[j].d, {p.w * p.l * p.d, p.w, -p.d *\
    \ p.w, -p.l * p.w});\n          bit.apply(rs[j].u, {-p.w * p.l * p.u, -p.w, p.u\
    \ * p.w, p.l * p.w});\n        }\n        ++j;\n      }\n      auto &p = queries[query.idx];\n\
    \      auto uret = bit.prod(query.u);\n      ans[query.idx] += uret[0];\n    \
    \  ans[query.idx] += uret[1] * query.x * p.u;\n      ans[query.idx] += uret[2]\
    \ * query.x;\n      ans[query.idx] += uret[3] * p.u;\n      auto dret = bit.prod(query.d);\n\
    \      ans[query.idx] -= dret[0];\n      ans[query.idx] -= dret[1] * query.x *\
    \ p.d;\n      ans[query.idx] -= dret[2] * query.x;\n      ans[query.idx] -= dret[3]\
    \ * p.d;\n      if(not query.type) ans[query.idx] *= -1;\n    }\n    return ans;\n\
    \  }\n};\n"
  code: "#include \"../structure/others/binary-indexed-tree.hpp\"\n\n/**\n * @brief\
    \ Static Rectangle Add Rectangle Sum\n */\ntemplate< typename T, typename C >\n\
    struct StaticRectangleAddRectangleSum {\n  struct Hikari : array< C, 4 > {\n \
    \   using A = array< C, 4 >;\n\n    Hikari &operator+=(const Hikari &p) {\n  \
    \    for(int i = 0; i < 4; i++) {\n        this->at(i) += p.at(i);\n      }\n\
    \      return *this;\n    }\n  };\n\n  using BIT = BinaryIndexedTree< Hikari >;\n\
    \n  static_assert(is_integral< T >::value, \"template parameter T must be integral\
    \ type\");\n\n  struct Rectangle {\n    T l, d, r, u;\n    C w;\n  };\n\n  struct\
    \ Query {\n    T l, d, r, u;\n  };\n\n  vector< Rectangle > rectangles;\n  vector<\
    \ Query > queries;\n\n  StaticRectangleAddRectangleSum() = default;\n\n  StaticRectangleAddRectangleSum(int\
    \ n, int q) {\n    rectangles.reserve(n);\n    queries.reserve(q);\n  }\n\n  void\
    \ add_rectangle(T l, T d, T r, T u, C w) {\n    rectangles.emplace_back(Rectangle{l,\
    \ d, r, u, w});\n  }\n\n  // total weight of [l, r) * [d, u) points\n  void add_query(T\
    \ l, T d, T r, T u) {\n    queries.emplace_back(Query{l, d, r, u});\n  }\n\n \
    \ vector< C > calculate_queries() {\n    int n = (int) rectangles.size();\n  \
    \  int q = (int) queries.size();\n    vector< C > ans(q);\n    if(rectangles.empty()\
    \ or queries.empty()) {\n      return ans;\n    }\n    vector< T > ys;\n    ys.reserve(n\
    \ + n);\n    for(Rectangle &p: rectangles) {\n      ys.emplace_back(p.d);\n  \
    \    ys.emplace_back(p.u);\n    }\n    sort(ys.begin(), ys.end());\n    ys.erase(unique(ys.begin(),\
    \ ys.end()), ys.end());\n\n    struct Q {\n      T x;\n      int d, u;\n     \
    \ bool type;\n      int idx;\n    };\n    vector< Q > rs, qs;\n    rs.reserve(n\
    \ + n);\n    qs.reserve(q + q);\n    for(int i = 0; i < n; i++) {\n      auto\
    \ &p = rectangles[i];\n      int d = lower_bound(ys.begin(), ys.end(), p.d) -\
    \ ys.begin();\n      int u = lower_bound(ys.begin(), ys.end(), p.u) - ys.begin();\n\
    \      rs.emplace_back(Q{p.l, d, u, false, i});\n      rs.emplace_back(Q{p.r,\
    \ d, u, true, i});\n    }\n    for(int i = 0; i < q; i++) {\n      auto &p = queries[i];\n\
    \      int d = lower_bound(ys.begin(), ys.end(), p.d) - ys.begin();\n      int\
    \ u = lower_bound(ys.begin(), ys.end(), p.u) - ys.begin();\n      qs.emplace_back(Q{p.l,\
    \ d, u, false, i});\n      qs.emplace_back(Q{p.r, d, u, true, i});\n    }\n  \
    \  sort(rs.begin(), rs.end(), [](const Q &a, const Q &b) {\n      return a.x <\
    \ b.x;\n    });\n    sort(qs.begin(), qs.end(), [](const Q &a, const Q &b) {\n\
    \      return a.x < b.x;\n    });\n    int j = 0;\n    BIT bit(ys.size());\n \
    \   for(auto &query: qs) {\n      while(j < n and rs[j].x < query.x) {\n     \
    \   auto &p = rectangles[j];\n        if(rs[j].type) {\n          bit.apply(rs[j].d,\
    \ {-p.w * p.r * p.d, -p.w, p.d * p.w, p.r * p.w});\n          bit.apply(rs[j].u,\
    \ {p.w * p.r * p.u, p.w, -p.u * p.w, -p.r * p.w});\n        } else {\n       \
    \   bit.apply(rs[j].d, {p.w * p.l * p.d, p.w, -p.d * p.w, -p.l * p.w});\n    \
    \      bit.apply(rs[j].u, {-p.w * p.l * p.u, -p.w, p.u * p.w, p.l * p.w});\n \
    \       }\n        ++j;\n      }\n      auto &p = queries[query.idx];\n      auto\
    \ uret = bit.prod(query.u);\n      ans[query.idx] += uret[0];\n      ans[query.idx]\
    \ += uret[1] * query.x * p.u;\n      ans[query.idx] += uret[2] * query.x;\n  \
    \    ans[query.idx] += uret[3] * p.u;\n      auto dret = bit.prod(query.d);\n\
    \      ans[query.idx] -= dret[0];\n      ans[query.idx] -= dret[1] * query.x *\
    \ p.d;\n      ans[query.idx] -= dret[2] * query.x;\n      ans[query.idx] -= dret[3]\
    \ * p.d;\n      if(not query.type) ans[query.idx] *= -1;\n    }\n    return ans;\n\
    \  }\n};\n"
  dependsOn:
  - structure/others/binary-indexed-tree.hpp
  isVerificationFile: false
  path: other/static-rectangle-add-rectangle-sum.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other/static-rectangle-add-rectangle-sum.hpp
layout: document
redirect_from:
- /library/other/static-rectangle-add-rectangle-sum.hpp
- /library/other/static-rectangle-add-rectangle-sum.hpp.html
title: Static Rectangle Add Rectangle Sum
---
