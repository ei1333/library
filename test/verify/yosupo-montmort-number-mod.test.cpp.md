---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/combinatorics/arbitrary-mod-int.hpp
    title: math/combinatorics/arbitrary-mod-int.hpp
  - icon: ':heavy_check_mark:'
    path: math/combinatorics/montmort.hpp
    title: "Montmort-Number(\u30E2\u30F3\u30E2\u30FC\u30EB\u6570)"
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
    PROBLEM: https://judge.yosupo.jp/problem/montmort_number_mod
    links:
    - https://judge.yosupo.jp/problem/montmort_number_mod
  bundledCode: "#line 1 \"test/verify/yosupo-montmort-number-mod.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/montmort_number_mod\"\n\n#line 1 \"\
    template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace std;\n\nusing\
    \ int64 = long long;\nconst int mod = 1e9 + 7;\n\nconst int64 infll = (1LL <<\
    \ 62) - 1;\nconst int inf = (1 << 30) - 1;\n\nstruct IoSetup {\n  IoSetup() {\n\
    \    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n    cout << fixed <<\
    \ setprecision(10);\n    cerr << fixed << setprecision(10);\n  }\n} iosetup;\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-montmort-number-mod.test.cpp\"\
    \n\n#line 1 \"math/combinatorics/arbitrary-mod-int.hpp\"\nstruct ArbitraryModInt\
    \ {\n\n  int x;\n\n  ArbitraryModInt() : x(0) {}\n\n  ArbitraryModInt(int64_t\
    \ y) : x(y >= 0 ? y % get_mod() : (get_mod() - (-y) % get_mod()) % get_mod())\
    \ {}\n\n  static int &get_mod() {\n    static int mod = 0;\n    return mod;\n\
    \  }\n\n  static void set_mod(int md) {\n    get_mod() = md;\n  }\n\n  ArbitraryModInt\
    \ &operator+=(const ArbitraryModInt &p) {\n    if((x += p.x) >= get_mod()) x -=\
    \ get_mod();\n    return *this;\n  }\n\n  ArbitraryModInt &operator-=(const ArbitraryModInt\
    \ &p) {\n    if((x += get_mod() - p.x) >= get_mod()) x -= get_mod();\n    return\
    \ *this;\n  }\n\n  ArbitraryModInt &operator*=(const ArbitraryModInt &p) {\n \
    \   unsigned long long a = (unsigned long long) x * p.x;\n    unsigned xh = (unsigned)\
    \ (a >> 32), xl = (unsigned) a, d, m;\n    asm(\"divl %4; \\n\\t\" : \"=a\" (d),\
    \ \"=d\" (m) : \"d\" (xh), \"a\" (xl), \"r\" (get_mod()));\n    x = m;\n    return\
    \ *this;\n  }\n\n  ArbitraryModInt &operator/=(const ArbitraryModInt &p) {\n \
    \   *this *= p.inverse();\n    return *this;\n  }\n\n  ArbitraryModInt operator-()\
    \ const { return ArbitraryModInt(-x); }\n\n  ArbitraryModInt operator+(const ArbitraryModInt\
    \ &p) const { return ArbitraryModInt(*this) += p; }\n\n  ArbitraryModInt operator-(const\
    \ ArbitraryModInt &p) const { return ArbitraryModInt(*this) -= p; }\n\n  ArbitraryModInt\
    \ operator*(const ArbitraryModInt &p) const { return ArbitraryModInt(*this) *=\
    \ p; }\n\n  ArbitraryModInt operator/(const ArbitraryModInt &p) const { return\
    \ ArbitraryModInt(*this) /= p; }\n\n  bool operator==(const ArbitraryModInt &p)\
    \ const { return x == p.x; }\n\n  bool operator!=(const ArbitraryModInt &p) const\
    \ { return x != p.x; }\n\n  ArbitraryModInt inverse() const {\n    int a = x,\
    \ b = get_mod(), u = 1, v = 0, t;\n    while(b > 0) {\n      t = a / b;\n    \
    \  swap(a -= t * b, b);\n      swap(u -= t * v, v);\n    }\n    return ArbitraryModInt(u);\n\
    \  }\n\n  ArbitraryModInt pow(int64_t n) const {\n    ArbitraryModInt ret(1),\
    \ mul(x);\n    while(n > 0) {\n      if(n & 1) ret *= mul;\n      mul *= mul;\n\
    \      n >>= 1;\n    }\n    return ret;\n  }\n\n  friend ostream &operator<<(ostream\
    \ &os, const ArbitraryModInt &p) {\n    return os << p.x;\n  }\n\n  friend istream\
    \ &operator>>(istream &is, ArbitraryModInt &a) {\n    int64_t t;\n    is >> t;\n\
    \    a = ArbitraryModInt(t);\n    return (is);\n  }\n};\n#line 1 \"math/combinatorics/montmort.hpp\"\
    \n/**\n * @brief Montmort-Number(\u30E2\u30F3\u30E2\u30FC\u30EB\u6570)\n * @docs\
    \ docs/montmort.md\n */\ntemplate< typename T >\nvector< T > montmort(int N) {\n\
    \  vector< T > dp(N + 1);\n  for(int k = 2; k <= N; k++) {\n    dp[k] = dp[k -\
    \ 1] * k;\n    if(k & 1) dp[k] -= 1;\n    else dp[k] += 1;\n  }\n  return dp;\n\
    }\n#line 7 \"test/verify/yosupo-montmort-number-mod.test.cpp\"\n\nint main() {\n\
    \  int N, M;\n  cin >> N >> M;\n  ArbitraryModInt::set_mod(M);\n  auto ret = montmort<\
    \ ArbitraryModInt >(N);\n  ret.erase(begin(ret));\n  cout << ret << endl;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/montmort_number_mod\"\n\
    \n#include \"../../template/template.hpp\"\n\n#include \"../../math/combinatorics/arbitrary-mod-int.hpp\"\
    \n#include \"../../math/combinatorics/montmort.hpp\"\n\nint main() {\n  int N,\
    \ M;\n  cin >> N >> M;\n  ArbitraryModInt::set_mod(M);\n  auto ret = montmort<\
    \ ArbitraryModInt >(N);\n  ret.erase(begin(ret));\n  cout << ret << endl;\n}\n"
  dependsOn:
  - template/template.hpp
  - math/combinatorics/arbitrary-mod-int.hpp
  - math/combinatorics/montmort.hpp
  isVerificationFile: true
  path: test/verify/yosupo-montmort-number-mod.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-montmort-number-mod.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-montmort-number-mod.test.cpp
- /verify/test/verify/yosupo-montmort-number-mod.test.cpp.html
title: test/verify/yosupo-montmort-number-mod.test.cpp
---
