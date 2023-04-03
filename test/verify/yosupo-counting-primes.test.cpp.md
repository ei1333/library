---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/number-theory/kth-root-integer.hpp
    title: Kth Root Integer
  - icon: ':heavy_check_mark:'
    path: math/number-theory/prime-count.hpp
    title: "Prime Count(\u7D20\u6570\u306E\u500B\u6570)"
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
    PROBLEM: https://judge.yosupo.jp/problem/counting_primes
    links:
    - https://judge.yosupo.jp/problem/counting_primes
  bundledCode: "#line 1 \"test/verify/yosupo-counting-primes.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/counting_primes\"\n\n#line 1 \"template/template.hpp\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-counting-primes.test.cpp\"\
    \n\n#line 1 \"math/number-theory/kth-root-integer.hpp\"\nuint64_t kth_root_integer(uint64_t\
    \ a, int k) {\n  if(k == 1) return a;\n  auto check = [&](uint32_t x) {\n    uint64_t\
    \ mul = 1;\n    for(int j = 0; j < k; j++) {\n      if(__builtin_mul_overflow(mul,\
    \ x, &mul)) return false;\n    }\n    return mul <= a;\n  };\n  uint64_t ret =\
    \ 0;\n  for(int i = 31; i >= 0; i--) {\n    if(check(ret | (1u << i))) ret |=\
    \ 1u << i;\n  }\n  return ret;\n}\n#line 1 \"math/number-theory/prime-table.hpp\"\
    \n/**\n * @brief Prime Table(\u7D20\u6570\u30C6\u30FC\u30D6\u30EB)\n * @docs docs/prime-table.md\n\
    \ */\nvector< bool > prime_table(int n) {\n  vector< bool > prime(n + 1, true);\n\
    \  if(n >= 0) prime[0] = false;\n  if(n >= 1) prime[1] = false;\n  for(int i =\
    \ 2; i * i <= n; i++) {\n    if(!prime[i]) continue;\n    for(int j = i * i; j\
    \ <= n; j += i) {\n      prime[j] = false;\n    }\n  }\n  return prime;\n}\n#line\
    \ 3 \"math/number-theory/prime-count.hpp\"\n\n/**\n * @brief Prime Count(\u7D20\
    \u6570\u306E\u500B\u6570)\n */\ntemplate< int64_t LIM = 100000000000LL >\nstruct\
    \ PrimeCount {\nprivate:\n  int64_t sq;\n  vector< bool > prime;\n  vector< int64_t\
    \ > prime_sum, primes;\n\n  int64_t p2(int64_t x, int64_t y) {\n    if(x < 4)\
    \ return 0;\n    int64_t a = pi(y);\n    int64_t b = pi(kth_root_integer(x, 2));\n\
    \    if(a >= b) return 0;\n    int64_t sum = (a - 2) * (a + 1) / 2 - (b - 2) *\
    \ (b + 1) / 2;\n    for(int64_t i = a; i < b; i++) sum += pi(x / primes[i]);\n\
    \    return sum;\n  }\n\n  int64_t phi(int64_t m, int64_t n) {\n    if(m < 1)\
    \ return 0;\n    if(n > m) return 1;\n    if(n < 1) return m;\n    if(m <= primes[n\
    \ - 1] * primes[n - 1]) return pi(m) - n + 1;\n    if(m <= primes[n - 1] * primes[n\
    \ - 1] * primes[n - 1] && m <= sq) {\n      int64_t sx = pi(kth_root_integer(m,\
    \ 2));\n      int64_t ans = pi(m) - (sx + n - 2) * (sx - n + 1) / 2;\n      for(int64_t\
    \ i = n; i < sx; ++i) ans += pi(m / primes[i]);\n      return ans;\n    }\n  \
    \  return phi(m, n - 1) - phi(m / primes[n - 1], n - 1);\n  }\n\npublic:\n\n \
    \ PrimeCount() : sq(kth_root_integer(LIM, 2)), prime_sum(sq + 1) {\n    prime\
    \ = prime_table(sq);\n    for(int i = 1; i <= sq; i++) prime_sum[i] = prime_sum[i\
    \ - 1] + prime[i];\n    primes.reserve(prime_sum[sq]);\n    for(int i = 1; i <=\
    \ sq; i++) if(prime[i]) primes.push_back(i);\n  }\n\n  int64_t pi(int64_t n) {\n\
    \    if(n <= sq) return prime_sum[n];\n    int64_t m = kth_root_integer(n, 3);\n\
    \    int64_t a = pi(m);\n    return phi(n, a) + a - 1 - p2(n, m);\n  }\n};\n#line\
    \ 6 \"test/verify/yosupo-counting-primes.test.cpp\"\n\nint main() {\n  int64_t\
    \ n;\n  cin >> n;\n  PrimeCount<> pc;\n  cout << pc.pi(n) << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/counting_primes\"\n\n#include\
    \ \"../../template/template.hpp\"\n\n#include \"../../math/number-theory/prime-count.hpp\"\
    \n\nint main() {\n  int64_t n;\n  cin >> n;\n  PrimeCount<> pc;\n  cout << pc.pi(n)\
    \ << \"\\n\";\n}\n"
  dependsOn:
  - template/template.hpp
  - math/number-theory/prime-count.hpp
  - math/number-theory/kth-root-integer.hpp
  - math/number-theory/prime-table.hpp
  isVerificationFile: true
  path: test/verify/yosupo-counting-primes.test.cpp
  requiredBy: []
  timestamp: '2022-10-23 21:05:11+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-counting-primes.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-counting-primes.test.cpp
- /verify/test/verify/yosupo-counting-primes.test.cpp.html
title: test/verify/yosupo-counting-primes.test.cpp
---
