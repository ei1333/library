---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: structure/union-find/weighted-union-find.hpp
    title: structure/union-find/weighted-union-find.hpp
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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B
  bundledCode: "#line 1 \"test/verify/aoj-dsl-1-b.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B\"\
    \n\n#line 1 \"template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace\
    \ std;\n\nusing int64 = long long;\nconst int mod = 1e9 + 7;\n\nconst int64 infll\
    \ = (1LL << 62) - 1;\nconst int inf = (1 << 30) - 1;\n\nstruct IoSetup {\n  IoSetup()\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-dsl-1-b.test.cpp\"\
    \n\n#line 1 \"structure/union-find/weighted-union-find.hpp\"\ntemplate< typename\
    \ T >\nstruct WeightedUnionFind {\n  vector< int > data;\n  vector< T > ws;\n\n\
    \  WeightedUnionFind() {}\n\n  WeightedUnionFind(int sz) : data(sz, -1), ws(sz)\
    \ {}\n\n  int find(int k) {\n    if(data[k] < 0) return k;\n    auto par = find(data[k]);\n\
    \    ws[k] += ws[data[k]];\n    return data[k] = par;\n  }\n\n  T weight(int t)\
    \ {\n    find(t);\n    return ws[t];\n  }\n\n  bool unite(int x, int y, T w) {\n\
    \    w += weight(x);\n    w -= weight(y);\n    x = find(x), y = find(y);\n   \
    \ if(x == y) return false;\n    if(data[x] > data[y]) {\n      swap(x, y);\n \
    \     w *= -1;\n    }\n    data[x] += data[y];\n    data[y] = x;\n    ws[y] =\
    \ w;\n    return true;\n  }\n\n  T diff(int x, int y) {\n    return weight(y)\
    \ - weight(x);\n  }\n};\n#line 6 \"test/verify/aoj-dsl-1-b.test.cpp\"\n\nint main()\
    \ {\n  int N, M;\n  cin >> N >> M;\n  WeightedUnionFind< int > tree(N);\n  while(M--)\
    \ {\n    int A, B, C, D;\n    cin >> A >> B >> C;\n    if(A == 0) {\n      cin\
    \ >> D;\n      tree.unite(B, C, D);\n    } else {\n      if(tree.find(B) == tree.find(C))\
    \ {\n        cout << tree.diff(B, C) << endl;\n      } else {\n        cout <<\
    \ \"?\" << endl;\n      }\n    }\n  }\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../structure/union-find/weighted-union-find.hpp\"\
    \n\nint main() {\n  int N, M;\n  cin >> N >> M;\n  WeightedUnionFind< int > tree(N);\n\
    \  while(M--) {\n    int A, B, C, D;\n    cin >> A >> B >> C;\n    if(A == 0)\
    \ {\n      cin >> D;\n      tree.unite(B, C, D);\n    } else {\n      if(tree.find(B)\
    \ == tree.find(C)) {\n        cout << tree.diff(B, C) << endl;\n      } else {\n\
    \        cout << \"?\" << endl;\n      }\n    }\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - structure/union-find/weighted-union-find.hpp
  isVerificationFile: true
  path: test/verify/aoj-dsl-1-b.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-dsl-1-b.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-dsl-1-b.test.cpp
- /verify/test/verify/aoj-dsl-1-b.test.cpp.html
title: test/verify/aoj-dsl-1-b.test.cpp
---
