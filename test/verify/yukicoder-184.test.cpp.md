---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/matrix/binary-basis.hpp
    title: math/matrix/binary-basis.hpp
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
    PROBLEM: https://yukicoder.me/problems/no/184
    links:
    - https://yukicoder.me/problems/no/184
  bundledCode: "#line 1 \"test/verify/yukicoder-184.test.cpp\"\n#define PROBLEM \"\
    https://yukicoder.me/problems/no/184\"\n\n#line 1 \"template/template.hpp\"\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yukicoder-184.test.cpp\"\
    \n\n#line 1 \"math/matrix/binary-basis.hpp\"\ntemplate< typename T >\nstruct BinaryBasis\
    \ {\n  vector< T > basis;\n  bool update;\n\n  BinaryBasis() : update(false) {}\n\
    \n  bool add(T bit) {\n    for(auto &p : basis) {\n      bit = min(bit, bit ^\
    \ p);\n    }\n    if(bit) {\n      basis.emplace_back(bit);\n      return update\
    \ = true;\n    } else {\n      return false;\n    }\n  }\n\n  bool check(T bit)\
    \ const {\n    for(auto &p : basis) {\n      bit = min(bit, bit ^ p);\n    }\n\
    \    return bit == 0;\n  }\n\n  void normalize() {\n    sweep();\n    for(int\
    \ i = (int) basis.size() - 1; i >= 0; i--) {\n      for(int j = i - 1; j >= 0;\
    \ j--) chmin(basis[i], basis[i] ^ basis[j]);\n    }\n  }\n\n  void sweep() {\n\
    \    if(exchange(update, false)) {\n      sort(begin(basis), end(basis));\n  \
    \  }\n  }\n\n  bool operator==(BinaryBasis< T > &a) {\n    normalize(), a.normalize();\n\
    \    return basis == a.basis;\n  }\n\n  T get_kth(int64_t k) { /* 0-indexed */\n\
    \    if((1LL << basis.size()) <= k) {\n      return -1;\n    }\n    T ret = T();\n\
    \    sweep();\n    for(int i = (int) basis.size() - 1; i >= 0; i--) {\n      if(k\
    \ < (1LL << i)) {\n        ret = min(ret, ret ^ basis[i]);\n      } else {\n \
    \       k -= 1LL << i;\n        ret = max(ret, ret ^ basis[i]);\n      }\n   \
    \ }\n    return ret;\n  }\n\n  size_t size() const {\n    return basis.size();\n\
    \  }\n};\n#line 6 \"test/verify/yukicoder-184.test.cpp\"\n\nint main() {\n  int\
    \ N;\n  cin >> N;\n  BinaryBasis< int64 > bb;\n  for(int i = 0; i < N; i++) {\n\
    \    int64 x;\n    cin >> x;\n    bb.add(x);\n  }\n  cout << (1LL << bb.size())\
    \ << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/184\"\n\n#include \"../../template/template.hpp\"\
    \n\n#include \"../../math/matrix/binary-basis.hpp\"\n\nint main() {\n  int N;\n\
    \  cin >> N;\n  BinaryBasis< int64 > bb;\n  for(int i = 0; i < N; i++) {\n   \
    \ int64 x;\n    cin >> x;\n    bb.add(x);\n  }\n  cout << (1LL << bb.size()) <<\
    \ \"\\n\";\n}\n"
  dependsOn:
  - template/template.hpp
  - math/matrix/binary-basis.hpp
  isVerificationFile: true
  path: test/verify/yukicoder-184.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yukicoder-184.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yukicoder-184.test.cpp
- /verify/test/verify/yukicoder-184.test.cpp.html
title: test/verify/yukicoder-184.test.cpp
---
