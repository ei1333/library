---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/number-theory/prime-table.hpp
    title: "Prime Table(\u7D20\u6570\u30C6\u30FC\u30D6\u30EB)"
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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_1_C
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_1_C
  bundledCode: "#line 1 \"test/verify/aoj-alds-1-1-c-2.test.cpp\"\n#define PROBLEM\
    \ \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_1_C\"\n\n#line\
    \ 1 \"template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace std;\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-alds-1-1-c-2.test.cpp\"\
    \n\n#line 1 \"math/number-theory/prime-table.hpp\"\n/**\n * @brief Prime Table(\u7D20\
    \u6570\u30C6\u30FC\u30D6\u30EB)\n * @docs docs/prime-table.md\n */\nvector< bool\
    \ > prime_table(int n) {\n  vector< bool > prime(n + 1, true);\n  if(n >= 0) prime[0]\
    \ = false;\n  if(n >= 1) prime[1] = false;\n  for(int i = 2; i * i <= n; i++)\
    \ {\n    if(!prime[i]) continue;\n    for(int j = i * i; j <= n; j += i) {\n \
    \     prime[j] = false;\n    }\n  }\n  return prime;\n}\n#line 6 \"test/verify/aoj-alds-1-1-c-2.test.cpp\"\
    \n\nint main() {\n  auto t = prime_table(100000000);\n  int N;\n  cin >> N;\n\
    \  int ret = 0;\n  while(N--) {\n    int x;\n    cin >> x;\n    ret += t[x];\n\
    \  }\n  cout << ret << endl;\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_1_C\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../math/number-theory/prime-table.hpp\"\
    \n\nint main() {\n  auto t = prime_table(100000000);\n  int N;\n  cin >> N;\n\
    \  int ret = 0;\n  while(N--) {\n    int x;\n    cin >> x;\n    ret += t[x];\n\
    \  }\n  cout << ret << endl;\n}\n"
  dependsOn:
  - template/template.hpp
  - math/number-theory/prime-table.hpp
  isVerificationFile: true
  path: test/verify/aoj-alds-1-1-c-2.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-alds-1-1-c-2.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-alds-1-1-c-2.test.cpp
- /verify/test/verify/aoj-alds-1-1-c-2.test.cpp.html
title: test/verify/aoj-alds-1-1-c-2.test.cpp
---
