---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: structure/others/persistent-array.hpp
    title: structure/others/persistent-array.hpp
  - icon: ':heavy_check_mark:'
    path: structure/union-find/persistent-union-find.hpp
    title: "Persistent-Union-Find(\u6C38\u7D9AUnion-Find)"
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
    PROBLEM: https://judge.yosupo.jp/problem/persistent_unionfind
    links:
    - https://judge.yosupo.jp/problem/persistent_unionfind
  bundledCode: "#line 1 \"test/verify/yosupo-persistent-unionfind.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/persistent_unionfind\"\n\n#line 1\
    \ \"template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace std;\n\
    \nusing int64 = long long;\nconst int mod = 1e9 + 7;\n\nconst int64 infll = (1LL\
    \ << 62) - 1;\nconst int inf = (1 << 30) - 1;\n\nstruct IoSetup {\n  IoSetup()\
    \ {\n    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n    cout << fixed\
    \ << setprecision(10);\n    cerr << fixed << setprecision(10);\n  }\n} iosetup;\n\
    \ntemplate< typename T1, typename T2 >\nostream &operator<<(ostream &os, const\
    \ pair< T1, T2 >& p) {\n  os << p.first << \" \" << p.second;\n  return os;\n\
    }\n\ntemplate< typename T1, typename T2 >\nistream &operator>>(istream &is, pair<\
    \ T1, T2 > &p) {\n  is >> p.first >> p.second;\n  return is;\n}\n\ntemplate< typename\
    \ T >\nostream &operator<<(ostream &os, const vector< T > &v) {\n  for(int i =\
    \ 0; i < (int) v.size(); i++) {\n    os << v[i] << (i + 1 != v.size() ? \" \"\
    \ : \"\");\n  }\n  return os;\n}\n\ntemplate< typename T >\nistream &operator>>(istream\
    \ &is, vector< T > &v) {\n  for(T &in : v) is >> in;\n  return is;\n}\n\ntemplate<\
    \ typename T1, typename T2 >\ninline bool chmax(T1 &a, T2 b) { return a < b &&\
    \ (a = b, true); }\n\ntemplate< typename T1, typename T2 >\ninline bool chmin(T1\
    \ &a, T2 b) { return a > b && (a = b, true); }\n\ntemplate< typename T = int64\
    \ >\nvector< T > make_v(size_t a) {\n  return vector< T >(a);\n}\n\ntemplate<\
    \ typename T, typename... Ts >\nauto make_v(size_t a, Ts... ts) {\n  return vector<\
    \ decltype(make_v< T >(ts...)) >(a, make_v< T >(ts...));\n}\n\ntemplate< typename\
    \ T, typename V >\ntypename enable_if< is_class< T >::value == 0 >::type fill_v(T\
    \ &t, const V &v) {\n  t = v;\n}\n\ntemplate< typename T, typename V >\ntypename\
    \ enable_if< is_class< T >::value != 0 >::type fill_v(T &t, const V &v) {\n  for(auto\
    \ &e : t) fill_v(e, v);\n}\n\ntemplate< typename F >\nstruct FixPoint : F {\n\
    \  explicit FixPoint(F &&f) : F(forward< F >(f)) {}\n\n  template< typename...\
    \ Args >\n  decltype(auto) operator()(Args &&... args) const {\n    return F::operator()(*this,\
    \ forward< Args >(args)...);\n  }\n};\n \ntemplate< typename F >\ninline decltype(auto)\
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-persistent-unionfind.test.cpp\"\
    \n\n#line 1 \"structure/others/persistent-array.hpp\"\ntemplate< typename T, int\
    \ LOG >\nstruct PersistentArray {\n  struct Node {\n    T data;\n    Node *child[1\
    \ << LOG] = {};\n\n    Node() {}\n\n    Node(const T &data) : data(data) {}\n\
    \  };\n\n  Node *root;\n\n  PersistentArray() : root(nullptr) {}\n\n  T get(Node\
    \ *t, int k) {\n    if(k == 0) return t->data;\n    return get(t->child[k & ((1\
    \ << LOG) - 1)], k >> LOG);\n  }\n\n  T get(const int &k) {\n    return get(root,\
    \ k);\n  }\n\n  pair< Node *, T * > mutable_get(Node *t, int k) {\n    t = t ?\
    \ new Node(*t) : new Node();\n    if(k == 0) return {t, &t->data};\n    auto p\
    \ = mutable_get(t->child[k & ((1 << LOG) - 1)], k >> LOG);\n    t->child[k & ((1\
    \ << LOG) - 1)] = p.first;\n    return {t, p.second};\n  }\n\n  T *mutable_get(const\
    \ int &k) {\n    auto ret = mutable_get(root, k);\n    root = ret.first;\n   \
    \ return ret.second;\n  }\n\n  Node *build(Node *t, const T &data, int k) {\n\
    \    if(!t) t = new Node();\n    if(k == 0) {\n      t->data = data;\n      return\
    \ t;\n    }\n    auto p = build(t->child[k & ((1 << LOG) - 1)], data, k >> LOG);\n\
    \    t->child[k & ((1 << LOG) - 1)] = p;\n    return t;\n  }\n\n  void build(const\
    \ vector< T > &v) {\n    root = nullptr;\n    for(int i = 0; i < v.size(); i++)\
    \ {\n      root = build(root, v[i], i);\n    }\n  }\n};\n\n#line 1 \"structure/union-find/persistent-union-find.hpp\"\
    \n/*\n * @brief Persistent-Union-Find(\u6C38\u7D9AUnion-Find)\n */\nstruct PersistentUnionFind\
    \ {\n  PersistentArray< int, 3 > data;\n\n  PersistentUnionFind() {}\n\n  PersistentUnionFind(int\
    \ sz) {\n    data.build(vector< int >(sz, -1));\n  }\n\n  int find(int k) {\n\
    \    int p = data.get(k);\n    return p >= 0 ? find(p) : k;\n  }\n\n  int size(int\
    \ k) {\n    return (-data.get(find(k)));\n  }\n\n  bool unite(int x, int y) {\n\
    \    x = find(x);\n    y = find(y);\n    if(x == y) return false;\n    auto u\
    \ = data.get(x);\n    auto v = data.get(y);\n\n    if(u < v) {\n      auto a =\
    \ data.mutable_get(x);\n      *a += v;\n      auto b = data.mutable_get(y);\n\
    \      *b = x;\n    } else {\n      auto a = data.mutable_get(y);\n      *a +=\
    \ u;\n      auto b = data.mutable_get(x);\n      *b = y;\n    }\n    return true;\n\
    \  }\n};\n#line 7 \"test/verify/yosupo-persistent-unionfind.test.cpp\"\n\nint\
    \ main() {\n  int N, Q;\n  cin >> N >> Q;\n  vector< PersistentUnionFind > uf(Q\
    \ + 1);\n  uf[0] = PersistentUnionFind(N);\n  for(int i = 1; i <= Q; i++) {\n\
    \    int t, k, u, v;\n    cin >> t >> k >> u >> v;\n    ++k;\n    if(t == 0) {\n\
    \      uf[i] = uf[k];\n      uf[i].unite(u, v);\n    } else {\n      cout << (uf[k].find(u)\
    \ == uf[k].find(v)) << \"\\n\";\n    }\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_unionfind\"\n\
    \n#include \"../../template/template.hpp\"\n\n#include \"../../structure/others/persistent-array.hpp\"\
    \n#include \"../../structure/union-find/persistent-union-find.hpp\"\n\nint main()\
    \ {\n  int N, Q;\n  cin >> N >> Q;\n  vector< PersistentUnionFind > uf(Q + 1);\n\
    \  uf[0] = PersistentUnionFind(N);\n  for(int i = 1; i <= Q; i++) {\n    int t,\
    \ k, u, v;\n    cin >> t >> k >> u >> v;\n    ++k;\n    if(t == 0) {\n      uf[i]\
    \ = uf[k];\n      uf[i].unite(u, v);\n    } else {\n      cout << (uf[k].find(u)\
    \ == uf[k].find(v)) << \"\\n\";\n    }\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - structure/others/persistent-array.hpp
  - structure/union-find/persistent-union-find.hpp
  isVerificationFile: true
  path: test/verify/yosupo-persistent-unionfind.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-persistent-unionfind.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-persistent-unionfind.test.cpp
- /verify/test/verify/yosupo-persistent-unionfind.test.cpp.html
title: test/verify/yosupo-persistent-unionfind.test.cpp
---
