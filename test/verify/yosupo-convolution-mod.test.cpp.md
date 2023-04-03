---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/fft/number-theoretic-transform.hpp
    title: math/fft/number-theoretic-transform.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod
    links:
    - https://judge.yosupo.jp/problem/convolution_mod
  bundledCode: "#line 1 \"test/verify/yosupo-convolution-mod.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/convolution_mod\"\n\n#line 1 \"template/template.hpp\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-convolution-mod.test.cpp\"\
    \n\n#line 1 \"math/fft/number-theoretic-transform.hpp\"\ntemplate< int mod >\n\
    struct NumberTheoreticTransform {\n\n  vector< int > rev, rts;\n  int base, max_base,\
    \ root;\n\n  NumberTheoreticTransform() : base(1), rev{0, 1}, rts{0, 1} {\n  \
    \  assert(mod >= 3 && mod % 2 == 1);\n    auto tmp = mod - 1;\n    max_base =\
    \ 0;\n    while(tmp % 2 == 0) tmp >>= 1, max_base++;\n    root = 2;\n    while(mod_pow(root,\
    \ (mod - 1) >> 1) == 1) ++root;\n    assert(mod_pow(root, mod - 1) == 1);\n  \
    \  root = mod_pow(root, (mod - 1) >> max_base);\n  }\n\n  inline int mod_pow(int\
    \ x, int n) {\n    int ret = 1;\n    while(n > 0) {\n      if(n & 1) ret = mul(ret,\
    \ x);\n      x = mul(x, x);\n      n >>= 1;\n    }\n    return ret;\n  }\n\n \
    \ inline int inverse(int x) {\n    return mod_pow(x, mod - 2);\n  }\n\n  inline\
    \ unsigned add(unsigned x, unsigned y) {\n    x += y;\n    if(x >= mod) x -= mod;\n\
    \    return x;\n  }\n\n  inline unsigned mul(unsigned a, unsigned b) {\n    return\
    \ 1ull * a * b % (unsigned long long) mod;\n  }\n\n  void ensure_base(int nbase)\
    \ {\n    if(nbase <= base) return;\n    rev.resize(1 << nbase);\n    rts.resize(1\
    \ << nbase);\n    for(int i = 0; i < (1 << nbase); i++) {\n      rev[i] = (rev[i\
    \ >> 1] >> 1) + ((i & 1) << (nbase - 1));\n    }\n    assert(nbase <= max_base);\n\
    \    while(base < nbase) {\n      int z = mod_pow(root, 1 << (max_base - 1 - base));\n\
    \      for(int i = 1 << (base - 1); i < (1 << base); i++) {\n        rts[i <<\
    \ 1] = rts[i];\n        rts[(i << 1) + 1] = mul(rts[i], z);\n      }\n      ++base;\n\
    \    }\n  }\n\n  void ntt(vector< int > &a) {\n    const int n = (int) a.size();\n\
    \    assert((n & (n - 1)) == 0);\n    int zeros = __builtin_ctz(n);\n    ensure_base(zeros);\n\
    \    int shift = base - zeros;\n    for(int i = 0; i < n; i++) {\n      if(i <\
    \ (rev[i] >> shift)) {\n        swap(a[i], a[rev[i] >> shift]);\n      }\n   \
    \ }\n    for(int k = 1; k < n; k <<= 1) {\n      for(int i = 0; i < n; i += 2\
    \ * k) {\n        for(int j = 0; j < k; j++) {\n          int z = mul(a[i + j\
    \ + k], rts[j + k]);\n          a[i + j + k] = add(a[i + j], mod - z);\n     \
    \     a[i + j] = add(a[i + j], z);\n        }\n      }\n    }\n  }\n\n  vector<\
    \ int > multiply(vector< int > a, vector< int > b) {\n    int need = a.size()\
    \ + b.size() - 1;\n    int nbase = 1;\n    while((1 << nbase) < need) nbase++;\n\
    \    ensure_base(nbase);\n    int sz = 1 << nbase;\n    a.resize(sz, 0);\n   \
    \ b.resize(sz, 0);\n    ntt(a);\n    ntt(b);\n    int inv_sz = inverse(sz);\n\
    \    for(int i = 0; i < sz; i++) {\n      a[i] = mul(a[i], mul(b[i], inv_sz));\n\
    \    }\n    reverse(a.begin() + 1, a.end());\n    ntt(a);\n    a.resize(need);\n\
    \    return a;\n  }\n};\n#line 6 \"test/verify/yosupo-convolution-mod.test.cpp\"\
    \n\nint main() {\n  int N, M;\n  cin >> N >> M;\n  vector< int > A(N), B(M);\n\
    \  for(auto &a : A) cin >> a;\n  for(auto &b : B) cin >> b;\n  NumberTheoreticTransform<\
    \ 998244353 > ntt;\n  for(auto &c : ntt.multiply(A, B)) cout << c << \" \";\n\
    \  cout << endl;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\n\n#include\
    \ \"../../template/template.hpp\"\n\n#include \"../../math/fft/number-theoretic-transform.hpp\"\
    \n\nint main() {\n  int N, M;\n  cin >> N >> M;\n  vector< int > A(N), B(M);\n\
    \  for(auto &a : A) cin >> a;\n  for(auto &b : B) cin >> b;\n  NumberTheoreticTransform<\
    \ 998244353 > ntt;\n  for(auto &c : ntt.multiply(A, B)) cout << c << \" \";\n\
    \  cout << endl;\n}\n"
  dependsOn:
  - template/template.hpp
  - math/fft/number-theoretic-transform.hpp
  isVerificationFile: true
  path: test/verify/yosupo-convolution-mod.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-convolution-mod.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-convolution-mod.test.cpp
- /verify/test/verify/yosupo-convolution-mod.test.cpp.html
title: test/verify/yosupo-convolution-mod.test.cpp
---
