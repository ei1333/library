---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: structure/others/abstract-2d-binary-indexed-tree-compressed.hpp
    title: "Abstract 2D Binary Indexed Tree Compressed(\u62BD\u8C61\u53162\u6B21\u5143\
      \u5EA7\u5727BIT)"
  - icon: ':heavy_check_mark:'
    path: structure/others/abstract-binary-indexed-tree.hpp
    title: "Abstract Binary Indexed Tree(\u62BD\u8C61\u5316BIT)"
  - icon: ':heavy_check_mark:'
    path: template/template.hpp
    title: template/template.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/1826
    links:
    - https://yukicoder.me/problems/no/1826
  bundledCode: "#line 1 \"test/verify/yukicoder-1826.test.cpp\"\n#define PROBLEM \"\
    https://yukicoder.me/problems/no/1826\"\n\n#line 1 \"template/template.hpp\"\n\
    #include<bits/stdc++.h>\n\nusing namespace std;\n\nusing int64 = long long;\n\
    const int mod = 1e9 + 7;\n\nconst int64 infll = (1LL << 62) - 1;\nconst int inf\
    \ = (1 << 30) - 1;\n\nstruct IoSetup {\n  IoSetup() {\n    cin.tie(nullptr);\n\
    \    ios::sync_with_stdio(false);\n    cout << fixed << setprecision(10);\n  \
    \  cerr << fixed << setprecision(10);\n  }\n} iosetup;\n\ntemplate< typename T1,\
    \ typename T2 >\nostream &operator<<(ostream &os, const pair< T1, T2 >& p) {\n\
    \  os << p.first << \" \" << p.second;\n  return os;\n}\n\ntemplate< typename\
    \ T1, typename T2 >\nistream &operator>>(istream &is, pair< T1, T2 > &p) {\n \
    \ is >> p.first >> p.second;\n  return is;\n}\n\ntemplate< typename T >\nostream\
    \ &operator<<(ostream &os, const vector< T > &v) {\n  for(int i = 0; i < (int)\
    \ v.size(); i++) {\n    os << v[i] << (i + 1 != v.size() ? \" \" : \"\");\n  }\n\
    \  return os;\n}\n\ntemplate< typename T >\nistream &operator>>(istream &is, vector<\
    \ T > &v) {\n  for(T &in : v) is >> in;\n  return is;\n}\n\ntemplate< typename\
    \ T1, typename T2 >\ninline bool chmax(T1 &a, T2 b) { return a < b && (a = b,\
    \ true); }\n\ntemplate< typename T1, typename T2 >\ninline bool chmin(T1 &a, T2\
    \ b) { return a > b && (a = b, true); }\n\ntemplate< typename T = int64 >\nvector<\
    \ T > make_v(size_t a) {\n  return vector< T >(a);\n}\n\ntemplate< typename T,\
    \ typename... Ts >\nauto make_v(size_t a, Ts... ts) {\n  return vector< decltype(make_v<\
    \ T >(ts...)) >(a, make_v< T >(ts...));\n}\n\ntemplate< typename T, typename V\
    \ >\ntypename enable_if< is_class< T >::value == 0 >::type fill_v(T &t, const\
    \ V &v) {\n  t = v;\n}\n\ntemplate< typename T, typename V >\ntypename enable_if<\
    \ is_class< T >::value != 0 >::type fill_v(T &t, const V &v) {\n  for(auto &e\
    \ : t) fill_v(e, v);\n}\n\ntemplate< typename F >\nstruct FixPoint : F {\n  explicit\
    \ FixPoint(F &&f) : F(forward< F >(f)) {}\n\n  template< typename... Args >\n\
    \  decltype(auto) operator()(Args &&... args) const {\n    return F::operator()(*this,\
    \ forward< Args >(args)...);\n  }\n};\n \ntemplate< typename F >\ninline decltype(auto)\
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yukicoder-1826.test.cpp\"\
    \n\n#line 1 \"structure/others/abstract-binary-indexed-tree.hpp\"\n/**\n * @brief\
    \ Abstract Binary Indexed Tree(\u62BD\u8C61\u5316BIT)\n */\ntemplate< typename\
    \ T, typename F >\nstruct AbstractBinaryIndexedTree {\nprivate:\n  int n;\n  vector<\
    \ T > data;\n  const F f;\n  const T e;\n\npublic:\n  AbstractBinaryIndexedTree()\
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
    \ f, e};\n}\n#line 6 \"test/verify/yukicoder-1826.test.cpp\"\n\nint main() {\n\
    \  int N;\n  cin >> N;\n  vector< tuple< int, int, int > > ds;\n  ds.reserve(N\
    \ + 1);\n  for(int i = 0; i < N; i++) {\n    int t, x, v;\n    cin >> t >> x >>\
    \ v;\n    ds.emplace_back(t, x, v);\n  }\n  ds.emplace_back(0, 0, 0);\n  sort(begin(ds),\
    \ end(ds));\n  vector< int64 > dp(ds.size(), -infll);\n  dp[0] = 0;\n  vector<\
    \ int > l, r;\n  vector< pair< int, int > > m;\n  l.reserve(N + 1);\n  r.reserve(N\
    \ + 1);\n  m.reserve(N + 1);\n  int ptr = 0;\n  for(auto&[t, x, v]: ds) {\n  \
    \  l.emplace_back(t + x);\n    r.emplace_back(t - x);\n    m.emplace_back(x, ptr++);\n\
    \  }\n  sort(begin(l), end(l));\n  l.erase(unique(begin(l), end(l)), end(l));\n\
    \  sort(begin(r), end(r));\n  r.erase(unique(begin(r), end(r)), end(r));\n  sort(begin(m),\
    \ end(m));\n  vector< int > ldx(ds.size()), rdx(ds.size()), mdx(ds.size());\n\
    \  for(int i = 0; i < (int) ds.size(); i++) {\n    auto[t, x, v]=ds[i];\n    ldx[i]\
    \ = lower_bound(begin(l), end(l), t + x) - begin(l);\n    rdx[i] = lower_bound(begin(r),\
    \ end(r), t - x) - begin(r);\n    mdx[i] = lower_bound(begin(m), end(m), make_pair(x,\
    \ i)) - begin(m);\n  }\n  auto f = [](int64 a, int64 b) { return max(a, b); };\n\
    \  // \u307F\u3093\u306A\u306E2D segment tree\n\n  vector< int > ladx(m.size()),\
    \ radx(m.size());\n  for(int i = 0; i < (int) ds.size(); i++) {\n    ladx[m.size()\
    \ - mdx[i] - 1] = ldx[i];\n    radx[mdx[i]] = rdx[i];\n  }\n  auto lseg = get_abstract_2d_binary_indexed_tree_compressed(ladx,\
    \ f, -infll);\n  auto rseg = get_abstract_2d_binary_indexed_tree_compressed(radx,\
    \ f, -infll);\n  vector< int > ord(ds.size());\n  lseg.apply(m.size() - mdx[0]\
    \ - 1, 0);\n  rseg.apply(mdx[0], 0);\n  int64 ret = 0;\n  for(int i = 1; i < (int)\
    \ ds.size(); i++) {\n    auto[t2, x2, v2] = ds[i];\n    auto v = max(lseg.prod(m.size()\
    \ - mdx[i], ldx[i] + 1), rseg.prod(mdx[i], rdx[i] + 1));\n    v += v2;\n    if(v\
    \ >= 0) {\n      chmax(ret, v);\n      lseg.apply(m.size() - mdx[i] - 1, v);\n\
    \      rseg.apply(mdx[i], v);\n    }\n  }\n  cout << ret << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1826\"\n\n#include \"\
    ../../template/template.hpp\"\n\n#include \"../../structure/others/abstract-2d-binary-indexed-tree-compressed.hpp\"\
    \n\nint main() {\n  int N;\n  cin >> N;\n  vector< tuple< int, int, int > > ds;\n\
    \  ds.reserve(N + 1);\n  for(int i = 0; i < N; i++) {\n    int t, x, v;\n    cin\
    \ >> t >> x >> v;\n    ds.emplace_back(t, x, v);\n  }\n  ds.emplace_back(0, 0,\
    \ 0);\n  sort(begin(ds), end(ds));\n  vector< int64 > dp(ds.size(), -infll);\n\
    \  dp[0] = 0;\n  vector< int > l, r;\n  vector< pair< int, int > > m;\n  l.reserve(N\
    \ + 1);\n  r.reserve(N + 1);\n  m.reserve(N + 1);\n  int ptr = 0;\n  for(auto&[t,\
    \ x, v]: ds) {\n    l.emplace_back(t + x);\n    r.emplace_back(t - x);\n    m.emplace_back(x,\
    \ ptr++);\n  }\n  sort(begin(l), end(l));\n  l.erase(unique(begin(l), end(l)),\
    \ end(l));\n  sort(begin(r), end(r));\n  r.erase(unique(begin(r), end(r)), end(r));\n\
    \  sort(begin(m), end(m));\n  vector< int > ldx(ds.size()), rdx(ds.size()), mdx(ds.size());\n\
    \  for(int i = 0; i < (int) ds.size(); i++) {\n    auto[t, x, v]=ds[i];\n    ldx[i]\
    \ = lower_bound(begin(l), end(l), t + x) - begin(l);\n    rdx[i] = lower_bound(begin(r),\
    \ end(r), t - x) - begin(r);\n    mdx[i] = lower_bound(begin(m), end(m), make_pair(x,\
    \ i)) - begin(m);\n  }\n  auto f = [](int64 a, int64 b) { return max(a, b); };\n\
    \  // \u307F\u3093\u306A\u306E2D segment tree\n\n  vector< int > ladx(m.size()),\
    \ radx(m.size());\n  for(int i = 0; i < (int) ds.size(); i++) {\n    ladx[m.size()\
    \ - mdx[i] - 1] = ldx[i];\n    radx[mdx[i]] = rdx[i];\n  }\n  auto lseg = get_abstract_2d_binary_indexed_tree_compressed(ladx,\
    \ f, -infll);\n  auto rseg = get_abstract_2d_binary_indexed_tree_compressed(radx,\
    \ f, -infll);\n  vector< int > ord(ds.size());\n  lseg.apply(m.size() - mdx[0]\
    \ - 1, 0);\n  rseg.apply(mdx[0], 0);\n  int64 ret = 0;\n  for(int i = 1; i < (int)\
    \ ds.size(); i++) {\n    auto[t2, x2, v2] = ds[i];\n    auto v = max(lseg.prod(m.size()\
    \ - mdx[i], ldx[i] + 1), rseg.prod(mdx[i], rdx[i] + 1));\n    v += v2;\n    if(v\
    \ >= 0) {\n      chmax(ret, v);\n      lseg.apply(m.size() - mdx[i] - 1, v);\n\
    \      rseg.apply(mdx[i], v);\n    }\n  }\n  cout << ret << \"\\n\";\n}\n"
  dependsOn:
  - template/template.hpp
  - structure/others/abstract-2d-binary-indexed-tree-compressed.hpp
  - structure/others/abstract-binary-indexed-tree.hpp
  isVerificationFile: true
  path: test/verify/yukicoder-1826.test.cpp
  requiredBy: []
  timestamp: '2022-10-23 21:27:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yukicoder-1826.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yukicoder-1826.test.cpp
- /verify/test/verify/yukicoder-1826.test.cpp.html
title: test/verify/yukicoder-1826.test.cpp
---
