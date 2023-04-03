---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: structure/others/abstract-binary-indexed-tree.hpp
    title: "Abstract Binary Indexed Tree(\u62BD\u8C61\u5316BIT)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-point-add-rectangle-sum-2.test.cpp
    title: test/verify/yosupo-point-add-rectangle-sum-2.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/verify/yukicoder-1826.test.cpp
    title: test/verify/yukicoder-1826.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Abstract 2D Binary Indexed Tree Compressed(\u62BD\u8C61\u5316\
      2\u6B21\u5143\u5EA7\u5727BIT)"
    links: []
  bundledCode: "#line 1 \"structure/others/abstract-binary-indexed-tree.hpp\"\n/**\n\
    \ * @brief Abstract Binary Indexed Tree(\u62BD\u8C61\u5316BIT)\n */\ntemplate<\
    \ typename T, typename F >\nstruct AbstractBinaryIndexedTree {\nprivate:\n  int\
    \ n;\n  vector< T > data;\n  const F f;\n  const T e;\n\npublic:\n  AbstractBinaryIndexedTree()\
    \ = default;\n\n  explicit AbstractBinaryIndexedTree(int n, const F f, const T\
    \ &e) : n(n), f(f), e(e) {\n    data.assign(n + 1, e);\n  }\n\n  explicit AbstractBinaryIndexedTree(const\
    \ vector< T > &v, const F f, const T &e) :\n      AbstractBinaryIndexedTree((int)\
    \ v.size(), f, e) {\n    build(v);\n  }\n\n  void build(const vector< T > &v)\
    \ {\n    assert(n == (int) v.size());\n    for(int i = 1; i <= n; i++) data[i]\
    \ = v[i - 1];\n    for(int i = 1; i <= n; i++) {\n      int j = i + (i & -i);\n\
    \      if(j <= n) data[j] = f(data[j], data[i]);\n    }\n  }\n\n  void apply(int\
    \ k, const T &x) {\n    for(++k; k <= n; k += k & -k) data[k] = f(data[k], x);\n\
    \  }\n\n  T prod(int r) const {\n    T ret{e};\n    for(; r > 0; r -= r & -r)\
    \ ret = f(ret, data[r]);\n    return ret;\n  }\n};\n\ntemplate< typename T, typename\
    \ F >\nAbstractBinaryIndexedTree< T, F > get_abstract_binary_indexed_tree(int\
    \ n, const F &f, const T &e) {\n  return AbstractBinaryIndexedTree{n, f, e};\n\
    }\n\ntemplate< typename T, typename F >\nAbstractBinaryIndexedTree< T, F > get_abstract_binary_indexed_tree(const\
    \ vector< T > &v, const F &f, const T &e) {\n  return AbstractBinaryIndexedTree{v,\
    \ f, e};\n}\n#line 2 \"structure/others/abstract-2d-binary-indexed-tree-compressed.hpp\"\
    \n\n/**\n * @brief Abstract 2D Binary Indexed Tree Compressed(\u62BD\u8C61\u5316\
    2\u6B21\u5143\u5EA7\u5727BIT)\n */\ntemplate< typename T, typename F >\nstruct\
    \ Abstract2DBinaryIndexedTreeCompressed {\nprivate:\n  int n;\n  vector< AbstractBinaryIndexedTree<\
    \ T, F > > data;\n  const F f;\n  const T e;\n  vector< int > hs;\n  vector< vector<\
    \ int > > beet;\npublic:\n  Abstract2DBinaryIndexedTreeCompressed(const vector<\
    \ int > &hs, const F f, const T &e) :\n      n((int) hs.size()), hs(hs), f(f),\
    \ e(e) {\n    vector< int > ord(n);\n    iota(begin(ord), end(ord), 0);\n    sort(begin(ord),\
    \ end(ord), [&](int a, int b) {\n      return hs[a] < hs[b];\n    });\n    beet.resize(n\
    \ + 1);\n    for(auto &&i: ord) {\n      for(int k = i + 1; k <= n; k += k & -k)\
    \ {\n        beet[k].emplace_back(hs[i]);\n      }\n    }\n    data.reserve(n\
    \ + 1);\n    for(int k = 0; k <= n; k++) {\n      beet[k].erase(unique(begin(beet[k]),\
    \ end(beet[k])), end(beet[k]));\n      data.emplace_back((int) beet[k].size(),\
    \ f, e);\n    }\n  }\n\n  void apply(int k1, const T &x) {\n    int k2 = hs[k1];\n\
    \    for(++k1; k1 <= n; k1 += k1 & -k1) {\n      int p = lower_bound(begin(beet[k1]),\
    \ end(beet[k1]), k2) - begin(beet[k1]);\n      data[k1].apply(p, x);\n    }\n\
    \  }\n\n  T prod(int r1, int r2) const {\n    T ret{e};\n    for(; r1 > 0; r1\
    \ -= r1 & -r1) {\n      int p = lower_bound(begin(beet[r1]), end(beet[r1]), r2)\
    \ - begin(beet[r1]);\n      ret = f(ret, data[r1].prod(p));\n    }\n    return\
    \ ret;\n  }\n};\n\ntemplate< typename T, typename F >\nAbstract2DBinaryIndexedTreeCompressed<\
    \ T, F > get_abstract_2d_binary_indexed_tree_compressed(const vector< int > &hs,\
    \ const F &f, const T &e) {\n  return Abstract2DBinaryIndexedTreeCompressed{hs,\
    \ f, e};\n}\n"
  code: "#include \"abstract-binary-indexed-tree.hpp\"\n\n/**\n * @brief Abstract\
    \ 2D Binary Indexed Tree Compressed(\u62BD\u8C61\u53162\u6B21\u5143\u5EA7\u5727\
    BIT)\n */\ntemplate< typename T, typename F >\nstruct Abstract2DBinaryIndexedTreeCompressed\
    \ {\nprivate:\n  int n;\n  vector< AbstractBinaryIndexedTree< T, F > > data;\n\
    \  const F f;\n  const T e;\n  vector< int > hs;\n  vector< vector< int > > beet;\n\
    public:\n  Abstract2DBinaryIndexedTreeCompressed(const vector< int > &hs, const\
    \ F f, const T &e) :\n      n((int) hs.size()), hs(hs), f(f), e(e) {\n    vector<\
    \ int > ord(n);\n    iota(begin(ord), end(ord), 0);\n    sort(begin(ord), end(ord),\
    \ [&](int a, int b) {\n      return hs[a] < hs[b];\n    });\n    beet.resize(n\
    \ + 1);\n    for(auto &&i: ord) {\n      for(int k = i + 1; k <= n; k += k & -k)\
    \ {\n        beet[k].emplace_back(hs[i]);\n      }\n    }\n    data.reserve(n\
    \ + 1);\n    for(int k = 0; k <= n; k++) {\n      beet[k].erase(unique(begin(beet[k]),\
    \ end(beet[k])), end(beet[k]));\n      data.emplace_back((int) beet[k].size(),\
    \ f, e);\n    }\n  }\n\n  void apply(int k1, const T &x) {\n    int k2 = hs[k1];\n\
    \    for(++k1; k1 <= n; k1 += k1 & -k1) {\n      int p = lower_bound(begin(beet[k1]),\
    \ end(beet[k1]), k2) - begin(beet[k1]);\n      data[k1].apply(p, x);\n    }\n\
    \  }\n\n  T prod(int r1, int r2) const {\n    T ret{e};\n    for(; r1 > 0; r1\
    \ -= r1 & -r1) {\n      int p = lower_bound(begin(beet[r1]), end(beet[r1]), r2)\
    \ - begin(beet[r1]);\n      ret = f(ret, data[r1].prod(p));\n    }\n    return\
    \ ret;\n  }\n};\n\ntemplate< typename T, typename F >\nAbstract2DBinaryIndexedTreeCompressed<\
    \ T, F > get_abstract_2d_binary_indexed_tree_compressed(const vector< int > &hs,\
    \ const F &f, const T &e) {\n  return Abstract2DBinaryIndexedTreeCompressed{hs,\
    \ f, e};\n}\n"
  dependsOn:
  - structure/others/abstract-binary-indexed-tree.hpp
  isVerificationFile: false
  path: structure/others/abstract-2d-binary-indexed-tree-compressed.hpp
  requiredBy: []
  timestamp: '2022-10-23 21:27:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yukicoder-1826.test.cpp
  - test/verify/yosupo-point-add-rectangle-sum-2.test.cpp
documentation_of: structure/others/abstract-2d-binary-indexed-tree-compressed.hpp
layout: document
redirect_from:
- /library/structure/others/abstract-2d-binary-indexed-tree-compressed.hpp
- /library/structure/others/abstract-2d-binary-indexed-tree-compressed.hpp.html
title: "Abstract 2D Binary Indexed Tree Compressed(\u62BD\u8C61\u53162\u6B21\u5143\
  \u5EA7\u5727BIT)"
---
