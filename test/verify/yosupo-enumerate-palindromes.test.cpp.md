---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/manacher.hpp
    title: "Manacher(\u6700\u9577\u56DE\u6587)"
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
    PROBLEM: https://judge.yosupo.jp/problem/enumerate_palindromes
    links:
    - https://judge.yosupo.jp/problem/enumerate_palindromes
  bundledCode: "#line 1 \"test/verify/yosupo-enumerate-palindromes.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/enumerate_palindromes\"\n\n#line 1\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-enumerate-palindromes.test.cpp\"\
    \n\n#line 1 \"string/manacher.hpp\"\n/**\n * @brief Manacher(\u6700\u9577\u56DE\
    \u6587)\n */\ntemplate< typename S >\nvector< int > manacher(S s, bool calc_even\
    \ = true) {\n  if(calc_even) {\n    int n = (int) s.size();\n    assert(n > 0);\n\
    \    s.resize(2 * n - 1);\n    for(int i = n - 1; i >= 0; i--) {\n      s[2 *\
    \ i] = s[i];\n    }\n    auto d = *min_element(begin(s), end(s));\n    for(int\
    \ i = 0; i < n - 1; i++) {\n      s[2 * i + 1] = d;\n    }\n  }\n  int n = (int)\
    \ s.size();\n  vector< int > rad(n);\n  {\n    int i = 0, j = 0;\n    while(i\
    \ < n) {\n      while(i - j >= 0 && i + j < n && s[i - j] == s[i + j]) ++j;\n\
    \      rad[i] = j;\n      int k = 1;\n      while(i - k >= 0 && i + k < n && k\
    \ + rad[i - k] < j) {\n        rad[i + k] = rad[i - k];\n        ++k;\n      }\n\
    \      i += k, j -= k;\n    }\n  }\n  if(calc_even) {\n    for(int i = 0; i <\
    \ n; i++) {\n      if(((i ^ rad[i]) & 1) == 0) rad[i]--;\n    }\n  } else {\n\
    \    for(auto &&x: rad) x = 2 * x - 1;\n  }\n  return rad;\n}\n#line 6 \"test/verify/yosupo-enumerate-palindromes.test.cpp\"\
    \n\nint main() {\n  string s;\n  cin >> s;\n  cout << manacher(s) << \"\\n\";\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_palindromes\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../string/manacher.hpp\"\
    \n\nint main() {\n  string s;\n  cin >> s;\n  cout << manacher(s) << \"\\n\";\n\
    }\n"
  dependsOn:
  - template/template.hpp
  - string/manacher.hpp
  isVerificationFile: true
  path: test/verify/yosupo-enumerate-palindromes.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-enumerate-palindromes.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-enumerate-palindromes.test.cpp
- /verify/test/verify/yosupo-enumerate-palindromes.test.cpp.html
title: test/verify/yosupo-enumerate-palindromes.test.cpp
---
