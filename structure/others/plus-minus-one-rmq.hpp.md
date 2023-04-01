---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: structure/others/sparse-table.hpp
    title: "Sparse-Table(\u30B9\u30D1\u30FC\u30B9\u30C6\u30FC\u30D6\u30EB)"
  _extendedRequiredBy:
  - icon: ':question:'
    path: graph/tree/pmormq-lowest-common-ancestor.hpp
    title: "PMORMQ-Lowest-Common-Ancestor(\u6700\u5C0F\u5171\u901A\u7956\u5148)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/aoj-grl-5-c-4.test.cpp
    title: test/verify/aoj-grl-5-c-4.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-lca.test.cpp
    title: test/verify/yosupo-lca.test.cpp
  - icon: ':x:'
    path: test/verify/yosupo-staticrmq-4.test.cpp
    title: test/verify/yosupo-staticrmq-4.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: Plus-Minus-One-RMQ
    links: []
  bundledCode: "#line 1 \"structure/others/sparse-table.hpp\"\n/**\n * @brief Sparse-Table(\u30B9\
    \u30D1\u30FC\u30B9\u30C6\u30FC\u30D6\u30EB)\n * @docs docs/sparse-table.md\n */\n\
    template< typename T, typename F >\nstruct SparseTable {\n  F f;\n  vector< vector<\
    \ T > > st;\n  vector< int > lookup;\n\n  SparseTable() = default;\n\n  explicit\
    \ SparseTable(const vector< T > &v, const F &f) : f(f) {\n    const int n = (int)\
    \ v.size();\n    const int b = 32 - __builtin_clz(n);\n    st.assign(b, vector<\
    \ T >(n));\n    for(int i = 0; i < v.size(); i++) {\n      st[0][i] = v[i];\n\
    \    }\n    for(int i = 1; i < b; i++) {\n      for(int j = 0; j + (1 << i) <=\
    \ n; j++) {\n        st[i][j] = f(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);\n\
    \      }\n    }\n    lookup.resize(v.size() + 1);\n    for(int i = 2; i < lookup.size();\
    \ i++) {\n      lookup[i] = lookup[i >> 1] + 1;\n    }\n  }\n\n  inline T fold(int\
    \ l, int r) const {\n    int b = lookup[r - l];\n    return f(st[b][l], st[b][r\
    \ - (1 << b)]);\n  }\n};\n\ntemplate< typename T, typename F >\nSparseTable< T,\
    \ F > get_sparse_table(const vector< T > &v, const F &f) {\n  return SparseTable<\
    \ T, F >(v, f);\n}\n#line 2 \"structure/others/plus-minus-one-rmq.hpp\"\n\n/**\n\
    \ * @brief Plus-Minus-One-RMQ\n **/\ntemplate< typename T >\nstruct PlusMinusOneRMQ\
    \ {\n  using F = function< int(int, int) >;\n\n  int backet;\n  vector< T > vs;\n\
    \  vector< int > bidx, bbit;\n  SparseTable< int, F > st;\n  vector< vector< vector<\
    \ int > > > lookup;\n\n  explicit PlusMinusOneRMQ() = default;\n\n  explicit PlusMinusOneRMQ(const\
    \ vector< T > &vs) : vs(vs) {\n    int n = (int) vs.size();\n    backet = max(1,\
    \ (31 - __builtin_clz(n)) / 2);\n    int sz = (n + backet - 1) / backet;\n   \
    \ bidx.assign(sz, -1);\n    bbit.assign(sz, 0);\n    for(int i = 0; i < sz; i++)\
    \ {\n      int l = i * backet;\n      int r = min(l + backet, n);\n      bidx[i]\
    \ = l;\n      for(int j = l + 1; j < r; j++) {\n        if(vs[j] < vs[bidx[i]])\
    \ bidx[i] = j;\n        if(vs[j - 1] < vs[j]) bbit[i] |= 1 << (j - l - 1);\n \
    \     }\n    }\n    F f = [&](int a, int b) { return vs[a] < vs[b] ? a : b; };\n\
    \    st = get_sparse_table(bidx, f);\n    lookup.assign(1 << (backet - 1), vector<\
    \ vector< int > >(backet, vector< int >(backet + 1)));\n    for(int i = 0; i <\
    \ (1 << (backet - 1)); i++) {\n      for(int j = 0; j < backet; j++) {\n     \
    \   int sum = 0, ret = 0, pos = j;\n        for(int k = j + 1; k <= backet; k++)\
    \ {\n          lookup[i][j][k] = pos;\n          if(i & (1 << (k - 1))) ++sum;\n\
    \          else --sum;\n          if(sum < ret) {\n            pos = k;\n    \
    \        ret = sum;\n          }\n        }\n      }\n    }\n  }\n\n  pair< T,\
    \ int > fold(int l, int r) const {\n    int lb = l / backet;\n    int rb = r /\
    \ backet;\n    if(lb == rb) {\n      int pos = lb * backet + lookup[bbit[lb]][l\
    \ % backet][r % backet];\n      return {vs[pos], pos};\n    }\n    int pos = lb\
    \ * backet + lookup[bbit[lb]][l % backet][backet];\n    if(r % backet > 0) {\n\
    \      int sub = rb * backet + lookup[bbit[rb]][0][r % backet];\n      if(vs[sub]\
    \ < vs[pos]) pos = sub;\n    }\n    if(lb + 1 == rb) {\n      return {vs[pos],\
    \ pos};\n    } else {\n      int sub = st.fold(lb + 1, rb);\n      if(vs[sub]\
    \ < vs[pos]) pos = sub;\n      return {vs[pos], pos};\n    }\n  }\n};\n"
  code: "#include \"sparse-table.hpp\"\n\n/**\n * @brief Plus-Minus-One-RMQ\n **/\n\
    template< typename T >\nstruct PlusMinusOneRMQ {\n  using F = function< int(int,\
    \ int) >;\n\n  int backet;\n  vector< T > vs;\n  vector< int > bidx, bbit;\n \
    \ SparseTable< int, F > st;\n  vector< vector< vector< int > > > lookup;\n\n \
    \ explicit PlusMinusOneRMQ() = default;\n\n  explicit PlusMinusOneRMQ(const vector<\
    \ T > &vs) : vs(vs) {\n    int n = (int) vs.size();\n    backet = max(1, (31 -\
    \ __builtin_clz(n)) / 2);\n    int sz = (n + backet - 1) / backet;\n    bidx.assign(sz,\
    \ -1);\n    bbit.assign(sz, 0);\n    for(int i = 0; i < sz; i++) {\n      int\
    \ l = i * backet;\n      int r = min(l + backet, n);\n      bidx[i] = l;\n   \
    \   for(int j = l + 1; j < r; j++) {\n        if(vs[j] < vs[bidx[i]]) bidx[i]\
    \ = j;\n        if(vs[j - 1] < vs[j]) bbit[i] |= 1 << (j - l - 1);\n      }\n\
    \    }\n    F f = [&](int a, int b) { return vs[a] < vs[b] ? a : b; };\n    st\
    \ = get_sparse_table(bidx, f);\n    lookup.assign(1 << (backet - 1), vector< vector<\
    \ int > >(backet, vector< int >(backet + 1)));\n    for(int i = 0; i < (1 << (backet\
    \ - 1)); i++) {\n      for(int j = 0; j < backet; j++) {\n        int sum = 0,\
    \ ret = 0, pos = j;\n        for(int k = j + 1; k <= backet; k++) {\n        \
    \  lookup[i][j][k] = pos;\n          if(i & (1 << (k - 1))) ++sum;\n         \
    \ else --sum;\n          if(sum < ret) {\n            pos = k;\n            ret\
    \ = sum;\n          }\n        }\n      }\n    }\n  }\n\n  pair< T, int > fold(int\
    \ l, int r) const {\n    int lb = l / backet;\n    int rb = r / backet;\n    if(lb\
    \ == rb) {\n      int pos = lb * backet + lookup[bbit[lb]][l % backet][r % backet];\n\
    \      return {vs[pos], pos};\n    }\n    int pos = lb * backet + lookup[bbit[lb]][l\
    \ % backet][backet];\n    if(r % backet > 0) {\n      int sub = rb * backet +\
    \ lookup[bbit[rb]][0][r % backet];\n      if(vs[sub] < vs[pos]) pos = sub;\n \
    \   }\n    if(lb + 1 == rb) {\n      return {vs[pos], pos};\n    } else {\n  \
    \    int sub = st.fold(lb + 1, rb);\n      if(vs[sub] < vs[pos]) pos = sub;\n\
    \      return {vs[pos], pos};\n    }\n  }\n};\n"
  dependsOn:
  - structure/others/sparse-table.hpp
  isVerificationFile: false
  path: structure/others/plus-minus-one-rmq.hpp
  requiredBy:
  - graph/tree/pmormq-lowest-common-ancestor.hpp
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/verify/yosupo-staticrmq-4.test.cpp
  - test/verify/yosupo-lca.test.cpp
  - test/verify/aoj-grl-5-c-4.test.cpp
documentation_of: structure/others/plus-minus-one-rmq.hpp
layout: document
redirect_from:
- /library/structure/others/plus-minus-one-rmq.hpp
- /library/structure/others/plus-minus-one-rmq.hpp.html
title: Plus-Minus-One-RMQ
---
