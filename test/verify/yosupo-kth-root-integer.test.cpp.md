---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/number-theory/kth-root-integer.hpp
    title: Kth Root Integer
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
    PROBLEM: https://judge.yosupo.jp/problem/kth_root_integer
    links:
    - https://judge.yosupo.jp/problem/kth_root_integer
  bundledCode: "#line 1 \"test/verify/yosupo-kth-root-integer.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/kth_root_integer\"\n\n#line 1 \"template/template.hpp\"\
    \n#include<bits/stdc++.h>\n\nusing namespace std;\n\nusing int64 = long long;\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-kth-root-integer.test.cpp\"\
    \n\n#line 1 \"math/number-theory/kth-root-integer.hpp\"\nuint64_t kth_root_integer(uint64_t\
    \ a, int k) {\n  if(k == 1) return a;\n  auto check = [&](uint32_t x) {\n    uint64_t\
    \ mul = 1;\n    for(int j = 0; j < k; j++) {\n      if(__builtin_mul_overflow(mul,\
    \ x, &mul)) return false;\n    }\n    return mul <= a;\n  };\n  uint64_t ret =\
    \ 0;\n  for(int i = 31; i >= 0; i--) {\n    if(check(ret | (1u << i))) ret |=\
    \ 1u << i;\n  }\n  return ret;\n}\n#line 6 \"test/verify/yosupo-kth-root-integer.test.cpp\"\
    \n\nint main() {\n  int T;\n  cin >> T;\n  while(T--) {\n    uint64_t a;\n   \
    \ int k;\n    cin >> a >> k;\n    cout << kth_root_integer(a, k) << \"\\n\";\n\
    \  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/kth_root_integer\"\n\n\
    #include \"../../template/template.hpp\"\n\n#include \"../../math/number-theory/kth-root-integer.hpp\"\
    \n\nint main() {\n  int T;\n  cin >> T;\n  while(T--) {\n    uint64_t a;\n   \
    \ int k;\n    cin >> a >> k;\n    cout << kth_root_integer(a, k) << \"\\n\";\n\
    \  }\n}\n"
  dependsOn:
  - template/template.hpp
  - math/number-theory/kth-root-integer.hpp
  isVerificationFile: true
  path: test/verify/yosupo-kth-root-integer.test.cpp
  requiredBy: []
  timestamp: '2022-10-23 21:05:11+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-kth-root-integer.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-kth-root-integer.test.cpp
- /verify/test/verify/yosupo-kth-root-integer.test.cpp.html
title: test/verify/yosupo-kth-root-integer.test.cpp
---
