---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/rolling-hash.hpp
    title: "Rolling-Hash(\u30ED\u30FC\u30EA\u30F3\u30B0\u30CF\u30C3\u30B7\u30E5)"
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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
  bundledCode: "#line 1 \"test/verify/aoj-alds-1-14-b.test.cpp\"\n#define PROBLEM\
    \ \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B\"\n\n\
    #line 1 \"template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-alds-1-14-b.test.cpp\"\
    \n\n#line 1 \"string/rolling-hash.hpp\"\n/**\n * @brief Rolling-Hash(\u30ED\u30FC\
    \u30EA\u30F3\u30B0\u30CF\u30C3\u30B7\u30E5)\n * @see https://qiita.com/keymoon/items/11fac5627672a6d6a9f6\n\
    \ * @docs docs/rolling-hash.md\n */\nstruct RollingHash {\n  static const uint64_t\
    \ mod = (1ull << 61ull) - 1;\n  using uint128_t = __uint128_t;\n  vector< uint64_t\
    \ > power;\n  const uint64_t base;\n\n  static inline uint64_t add(uint64_t a,\
    \ uint64_t b) {\n    if((a += b) >= mod) a -= mod;\n    return a;\n  }\n\n  static\
    \ inline uint64_t mul(uint64_t a, uint64_t b) {\n    uint128_t c = (uint128_t)\
    \ a * b;\n    return add(c >> 61, c & mod);\n  }\n\n  static inline uint64_t generate_base()\
    \ {\n    mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());\n\
    \    uniform_int_distribution< uint64_t > rand(1, RollingHash::mod - 1);\n   \
    \ return rand(mt);\n  }\n\n  inline void expand(size_t sz) {\n    if(power.size()\
    \ < sz + 1) {\n      int pre_sz = (int) power.size();\n      power.resize(sz +\
    \ 1);\n      for(int i = pre_sz - 1; i < sz; i++) {\n        power[i + 1] = mul(power[i],\
    \ base);\n      }\n    }\n  }\n\n  explicit RollingHash(uint64_t base = generate_base())\
    \ : base(base), power{1} {}\n\n  vector< uint64_t > build(const string &s) const\
    \ {\n    int sz = s.size();\n    vector< uint64_t > hashed(sz + 1);\n    for(int\
    \ i = 0; i < sz; i++) {\n      hashed[i + 1] = add(mul(hashed[i], base), s[i]);\n\
    \    }\n    return hashed;\n  }\n\n  template< typename T >\n  vector< uint64_t\
    \ > build(const vector< T > &s) const {\n    int sz = s.size();\n    vector< uint64_t\
    \ > hashed(sz + 1);\n    for(int i = 0; i < sz; i++) {\n      hashed[i + 1] =\
    \ add(mul(hashed[i], base), s[i]);\n    }\n    return hashed;\n  }\n\n  uint64_t\
    \ query(const vector< uint64_t > &s, int l, int r) {\n    expand(r - l);\n   \
    \ return add(s[r], mod - mul(s[l], power[r - l]));\n  }\n\n  uint64_t combine(uint64_t\
    \ h1, uint64_t h2, size_t h2len) {\n    expand(h2len);\n    return add(mul(h1,\
    \ power[h2len]), h2);\n  }\n\n  int lcp(const vector< uint64_t > &a, int l1, int\
    \ r1, const vector< uint64_t > &b, int l2, int r2) {\n    int len = min(r1 - l1,\
    \ r2 - l2);\n    int low = 0, high = len + 1;\n    while(high - low > 1) {\n \
    \     int mid = (low + high) / 2;\n      if(query(a, l1, l1 + mid) == query(b,\
    \ l2, l2 + mid)) low = mid;\n      else high = mid;\n    }\n    return low;\n\
    \  }\n};\n#line 6 \"test/verify/aoj-alds-1-14-b.test.cpp\"\n\nint main() {\n \
    \ string T, P;\n  cin >> T;\n  cin >> P;\n  RollingHash roll;\n  auto rh1 = roll.build(T);\n\
    \  auto rh2 = roll.build(P);\n  for(int i = 0; i + P.size() <= T.size(); i++)\
    \ {\n    if(roll.query(rh1, i, i + P.size()) == roll.query(rh2, 0, P.size()))\
    \ {\n      cout << i << endl;\n    }\n  }\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../string/rolling-hash.hpp\"\
    \n\nint main() {\n  string T, P;\n  cin >> T;\n  cin >> P;\n  RollingHash roll;\n\
    \  auto rh1 = roll.build(T);\n  auto rh2 = roll.build(P);\n  for(int i = 0; i\
    \ + P.size() <= T.size(); i++) {\n    if(roll.query(rh1, i, i + P.size()) == roll.query(rh2,\
    \ 0, P.size())) {\n      cout << i << endl;\n    }\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - string/rolling-hash.hpp
  isVerificationFile: true
  path: test/verify/aoj-alds-1-14-b.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-alds-1-14-b.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-alds-1-14-b.test.cpp
- /verify/test/verify/aoj-alds-1-14-b.test.cpp.html
title: test/verify/aoj-alds-1-14-b.test.cpp
---
