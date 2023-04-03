---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/number-theory/fast-prime-factorization.hpp
    title: math/number-theory/fast-prime-factorization.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/factorize
    links:
    - https://judge.yosupo.jp/problem/factorize
  bundledCode: "#line 1 \"test/verify/yosupo-factorize.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/factorize\"\n\n#line 1 \"template/template.hpp\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-factorize.test.cpp\"\
    \n\n#line 1 \"math/number-theory/fast-prime-factorization.hpp\"\nnamespace FastPrimeFactorization\
    \ {\n\n  template< typename word, typename dword, typename sword >\n  struct UnsafeMod\
    \ {\n    UnsafeMod() : x(0) {}\n\n    UnsafeMod(word _x) : x(init(_x)) {}\n\n\
    \    bool operator==(const UnsafeMod &rhs) const {\n      return x == rhs.x;\n\
    \    }\n\n    bool operator!=(const UnsafeMod &rhs) const {\n      return x !=\
    \ rhs.x;\n    }\n\n    UnsafeMod &operator+=(const UnsafeMod &rhs) {\n      if((x\
    \ += rhs.x) >= mod) x -= mod;\n      return *this;\n    }\n\n    UnsafeMod &operator-=(const\
    \ UnsafeMod &rhs) {\n      if(sword(x -= rhs.x) < 0) x += mod;\n      return *this;\n\
    \    }\n\n    UnsafeMod &operator*=(const UnsafeMod &rhs) {\n      x = reduce(dword(x)\
    \ * rhs.x);\n      return *this;\n    }\n\n    UnsafeMod operator+(const UnsafeMod\
    \ &rhs) const {\n      return UnsafeMod(*this) += rhs;\n    }\n\n    UnsafeMod\
    \ operator-(const UnsafeMod &rhs) const {\n      return UnsafeMod(*this) -= rhs;\n\
    \    }\n\n    UnsafeMod operator*(const UnsafeMod &rhs) const {\n      return\
    \ UnsafeMod(*this) *= rhs;\n    }\n\n    UnsafeMod pow(uint64_t e) const {\n \
    \     UnsafeMod ret(1);\n      for(UnsafeMod base = *this; e; e >>= 1, base *=\
    \ base) {\n        if(e & 1) ret *= base;\n      }\n      return ret;\n    }\n\
    \n    word get() const {\n      return reduce(x);\n    }\n\n    static constexpr\
    \ int word_bits = sizeof(word) * 8;\n\n    static word modulus() {\n      return\
    \ mod;\n    }\n\n    static word init(word w) {\n      return reduce(dword(w)\
    \ * r2);\n    }\n\n    static void set_mod(word m) {\n      mod = m;\n      inv\
    \ = mul_inv(mod);\n      r2 = -dword(mod) % mod;\n    }\n\n    static word reduce(dword\
    \ x) {\n      word y = word(x >> word_bits) - word((dword(word(x) * inv) * mod)\
    \ >> word_bits);\n      return sword(y) < 0 ? y + mod : y;\n    }\n\n    static\
    \ word mul_inv(word n, int e = 6, word x = 1) {\n      return !e ? x : mul_inv(n,\
    \ e - 1, x * (2 - x * n));\n    }\n\n    static word mod, inv, r2;\n\n    word\
    \ x;\n  };\n\n  using uint128_t = __uint128_t;\n\n  using Mod64 = UnsafeMod< uint64_t,\
    \ uint128_t, int64_t >;\n  template<> uint64_t Mod64::mod = 0;\n  template<> uint64_t\
    \ Mod64::inv = 0;\n  template<> uint64_t Mod64::r2 = 0;\n\n  using Mod32 = UnsafeMod<\
    \ uint32_t, uint64_t, int32_t >;\n  template<> uint32_t Mod32::mod = 0;\n  template<>\
    \ uint32_t Mod32::inv = 0;\n  template<> uint32_t Mod32::r2 = 0;\n\n  bool miller_rabin_primality_test_uint64(uint64_t\
    \ n) {\n    Mod64::set_mod(n);\n    uint64_t d = n - 1;\n    while(d % 2 == 0)\
    \ d /= 2;\n    Mod64 e{1}, rev{n - 1};\n    // http://miller-rabin.appspot.com/\
    \  < 2^64\n    for(uint64_t a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022})\
    \ {\n      if(n <= a) break;\n      uint64_t t = d;\n      Mod64 y = Mod64(a).pow(t);\n\
    \      while(t != n - 1 && y != e && y != rev) {\n        y *= y;\n        t *=\
    \ 2;\n      }\n      if(y != rev && t % 2 == 0) return false;\n    }\n    return\
    \ true;\n  }\n\n  bool miller_rabin_primality_test_uint32(uint32_t n) {\n    Mod32::set_mod(n);\n\
    \    uint32_t d = n - 1;\n    while(d % 2 == 0) d /= 2;\n    Mod32 e{1}, rev{n\
    \ - 1};\n    for(uint32_t a : {2, 7, 61}) {\n      if(n <= a) break;\n      uint32_t\
    \ t = d;\n      Mod32 y = Mod32(a).pow(t);\n      while(t != n - 1 && y != e &&\
    \ y != rev) {\n        y *= y;\n        t *= 2;\n      }\n      if(y != rev &&\
    \ t % 2 == 0) return false;\n    }\n    return true;\n  }\n\n  bool is_prime(uint64_t\
    \ n) {\n    if(n == 2) return true;\n    if(n == 1 || n % 2 == 0) return false;\n\
    \    if(n < uint64_t(1) << 31) return miller_rabin_primality_test_uint32(n);\n\
    \    return miller_rabin_primality_test_uint64(n);\n  }\n\n  uint64_t pollard_rho(uint64_t\
    \ n) {\n    if(is_prime(n)) return n;\n    if(n % 2 == 0) return 2;\n    Mod64::set_mod(n);\n\
    \    uint64_t d;\n    Mod64 one{1};\n    for(Mod64 c{one};; c += one) {\n    \
    \  Mod64 x{2}, y{2};\n      do {\n        x = x * x + c;\n        y = y * y +\
    \ c;\n        y = y * y + c;\n        d = __gcd((x - y).get(), n);\n      } while(d\
    \ == 1);\n      if(d < n) return d;\n    }\n    assert(0);\n  }\n\n  vector< uint64_t\
    \ > prime_factor(uint64_t n) {\n    if(n <= 1) return {};\n    uint64_t p = pollard_rho(n);\n\
    \    if(p == n) return {p};\n    auto l = prime_factor(p);\n    auto r = prime_factor(n\
    \ / p);\n    copy(begin(r), end(r), back_inserter(l));\n    return l;\n  }\n};\n\
    #line 6 \"test/verify/yosupo-factorize.test.cpp\"\n\nint main() {\n  int Q;\n\
    \  cin >> Q;\n  while(Q--) {\n    int64 X;\n    cin >> X;\n    auto ret = FastPrimeFactorization::prime_factor(X);\n\
    \    sort(begin(ret), end(ret));\n    cout << ret.size() << \" \";\n    cout <<\
    \ ret << \"\\n\";\n  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/factorize\"\n\n#include\
    \ \"../../template/template.hpp\"\n\n#include \"../../math/number-theory/fast-prime-factorization.hpp\"\
    \n\nint main() {\n  int Q;\n  cin >> Q;\n  while(Q--) {\n    int64 X;\n    cin\
    \ >> X;\n    auto ret = FastPrimeFactorization::prime_factor(X);\n    sort(begin(ret),\
    \ end(ret));\n    cout << ret.size() << \" \";\n    cout << ret << \"\\n\";\n\
    \  }\n}\n"
  dependsOn:
  - template/template.hpp
  - math/number-theory/fast-prime-factorization.hpp
  isVerificationFile: true
  path: test/verify/yosupo-factorize.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-factorize.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-factorize.test.cpp
- /verify/test/verify/yosupo-factorize.test.cpp.html
title: test/verify/yosupo-factorize.test.cpp
---
