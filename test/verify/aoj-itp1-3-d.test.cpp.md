---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/number-theory/divisor.hpp
    title: "Divisor(\u7D04\u6570\u5217\u6319)"
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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_3_D
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_3_D
  bundledCode: "#line 1 \"test/verify/aoj-itp1-3-d.test.cpp\"\n#define PROBLEM \"\
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_3_D\"\n\n#line 1\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-itp1-3-d.test.cpp\"\
    \n\n#line 1 \"math/number-theory/divisor.hpp\"\nvector< int64_t > divisor(int64_t\
    \ n) {\n  vector< int64_t > ret;\n  for(int64_t i = 1; i * i <= n; i++) {\n  \
    \  if(n % i == 0) {\n      ret.push_back(i);\n      if(i * i != n) ret.push_back(n\
    \ / i);\n    }\n  }\n  sort(begin(ret), end(ret));\n  return ret;\n}\n#line 6\
    \ \"test/verify/aoj-itp1-3-d.test.cpp\"\n\nint main() {\n  int A, B, C;\n  cin\
    \ >> A >> B >> C;\n  int ret = 0;\n  for(auto &p : divisor(C)) {\n    ret += A\
    \ <= p and p <= B;\n  }\n  cout << ret << \"\\n\";\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_3_D\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../math/number-theory/divisor.hpp\"\
    \n\nint main() {\n  int A, B, C;\n  cin >> A >> B >> C;\n  int ret = 0;\n  for(auto\
    \ &p : divisor(C)) {\n    ret += A <= p and p <= B;\n  }\n  cout << ret << \"\\\
    n\";\n}\n"
  dependsOn:
  - template/template.hpp
  - math/number-theory/divisor.hpp
  isVerificationFile: true
  path: test/verify/aoj-itp1-3-d.test.cpp
  requiredBy: []
  timestamp: '2022-10-23 20:41:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-itp1-3-d.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-itp1-3-d.test.cpp
- /verify/test/verify/aoj-itp1-3-d.test.cpp.html
title: test/verify/aoj-itp1-3-d.test.cpp
---
