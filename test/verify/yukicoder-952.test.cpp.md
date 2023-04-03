---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: structure/convex-hull-trick/convex-hull-trick-add-monotone.hpp
    title: Convex Hull Trick Add Monotone
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
    PROBLEM: https://yukicoder.me/problems/no/952
    links:
    - https://yukicoder.me/problems/no/952
  bundledCode: "#line 1 \"test/verify/yukicoder-952.test.cpp\"\n#define PROBLEM \"\
    https://yukicoder.me/problems/no/952\"\n\n#line 1 \"template/template.hpp\"\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yukicoder-952.test.cpp\"\
    \n\n#line 1 \"structure/convex-hull-trick/convex-hull-trick-add-monotone.hpp\"\
    \n/**\n * @brief Convex Hull Trick Add Monotone\n * @docs docs/convex-hull-trick-add-monotone.md\n\
    */\ntemplate< typename T, bool isMin >\nstruct ConvexHullTrickAddMonotone {\n\
    #define F first\n#define S second\n  using P = pair< T, T >;\n  deque< P > H;\n\
    \n  ConvexHullTrickAddMonotone() = default;\n\n  bool empty() const { return H.empty();\
    \ }\n\n  void clear() { H.clear(); }\n\n  inline int sgn(T x) { return x == 0\
    \ ? 0 : (x < 0 ? -1 : 1); }\n\n  inline bool check(const P &a, const P &b, const\
    \ P &c) {\n    if(b.S == a.S || c.S == b.S)\n      return sgn(b.F - a.F) * sgn(c.S\
    \ - b.S) >= sgn(c.F - b.F) * sgn(b.S - a.S);\n    //return (b.F-a.F)*(c.S-b.S)\
    \ >= (b.S-a.S)*(c.F-b.F);\n    if(is_integral< T >::value) {\n      return (b.S\
    \ - a.S) / (a.F - b.F) >= (c.S - b.S) / (b.F - c.F);\n    } else {\n      return\n\
    \          (b.F - a.F) * sgn(c.S - b.S) / abs(b.S - a.S) >=\n          (c.F -\
    \ b.F) * sgn(b.S - a.S) / abs(c.S - b.S);\n    }\n  }\n\n  void add(T a, T b)\
    \ {\n    if(!isMin) a *= -1, b *= -1;\n    P line(a, b);\n    if(empty()) {\n\
    \      H.emplace_front(line);\n      return;\n    }\n    if(H.front().F <= a)\
    \ {\n      if(H.front().F == a) {\n        if(H.front().S <= b) return;\n    \
    \    H.pop_front();\n      }\n      while(H.size() >= 2 && check(line, H.front(),\
    \ H[1])) H.pop_front();\n      H.emplace_front(line);\n    } else {\n      assert(a\
    \ <= H.back().F);\n      if(H.back().F == a) {\n        if(H.back().S <= b) return;\n\
    \        H.pop_back();\n      }\n      while(H.size() >= 2 && check(H[H.size()\
    \ - 2], H.back(), line)) H.pop_back();\n      H.emplace_back(line);\n    }\n \
    \ }\n\n  inline T get_y(const P &a, const T &x) {\n    return a.F * x + a.S;\n\
    \  }\n\n  T query(T x) {\n    assert(!empty());\n    int l = -1, r = H.size()\
    \ - 1;\n    while(l + 1 < r) {\n      int m = (l + r) >> 1;\n      if(get_y(H[m],\
    \ x) >= get_y(H[m + 1], x)) l = m;\n      else r = m;\n    }\n    if(isMin) return\
    \ get_y(H[r], x);\n    return -get_y(H[r], x);\n  }\n\n  T query_monotone_inc(T\
    \ x) {\n    assert(!empty());\n    while(H.size() >= 2 && get_y(H.front(), x)\
    \ >= get_y(H[1], x)) H.pop_front();\n    if(isMin) return get_y(H.front(), x);\n\
    \    return -get_y(H.front(), x);\n  }\n\n  T query_monotone_dec(T x) {\n    assert(!empty());\n\
    \    while(H.size() >= 2 && get_y(H.back(), x) >= get_y(H[H.size() - 2], x)) H.pop_back();\n\
    \    if(isMin) return get_y(H.back(), x);\n    return -get_y(H.back(), x);\n \
    \ }\n\n#undef F\n#undef S\n};\n#line 6 \"test/verify/yukicoder-952.test.cpp\"\n\
    \nint main() {\n  int N;\n  cin >> N;\n  vector< int > A(N);\n  cin >> A;\n  vector<\
    \ int64 > S(N + 2);\n  for(int i = 0; i < N; i++) {\n    S[i + 1] = S[i] + A[i];\n\
    \  }\n\n  auto dp = make_v< int64 >(N + 2, N + 1);\n  auto dp2 = make_v< int64\
    \ >(N + 2, N + 1);\n  fill_v(dp, infll);\n  fill_v(dp2, infll);\n  dp[0][0] =\
    \ 0;\n\n  vector< ConvexHullTrickAddMonotone< int64, true > > chts(2 * N + 10);\n\
    \  const int Shift = N + 5;\n\n  for(int i = 0; i <= N + 1; i++) {\n    if(i <=\
    \ N) {\n      for(int j = 0; j <= N; j++) {\n        int Q = j - i + Shift;\n\
    \        if(!chts[Q].empty()) chmin(dp2[i + 1][j], S[i] * S[i] + chts[Q].query_monotone_dec(-2\
    \ * S[i]));\n      }\n    }\n    for(int j = 0; j <= N; j++) {\n      if(i) dp[i][j]\
    \ = min(dp[i - 1][j], dp2[i][j]);\n      if(dp[i][j] != infll) chts[j - i + Shift].add(S[i],\
    \ dp[i][j] + S[i] * S[i]);\n    }\n  }\n\n  for(int i = 1; i <= N; i++) {\n  \
    \  cout << dp[N + 1][i] << endl;\n  }\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/952\"\n\n#include \"../../template/template.hpp\"\
    \n\n#include \"../../structure/convex-hull-trick/convex-hull-trick-add-monotone.hpp\"\
    \n\nint main() {\n  int N;\n  cin >> N;\n  vector< int > A(N);\n  cin >> A;\n\
    \  vector< int64 > S(N + 2);\n  for(int i = 0; i < N; i++) {\n    S[i + 1] = S[i]\
    \ + A[i];\n  }\n\n  auto dp = make_v< int64 >(N + 2, N + 1);\n  auto dp2 = make_v<\
    \ int64 >(N + 2, N + 1);\n  fill_v(dp, infll);\n  fill_v(dp2, infll);\n  dp[0][0]\
    \ = 0;\n\n  vector< ConvexHullTrickAddMonotone< int64, true > > chts(2 * N + 10);\n\
    \  const int Shift = N + 5;\n\n  for(int i = 0; i <= N + 1; i++) {\n    if(i <=\
    \ N) {\n      for(int j = 0; j <= N; j++) {\n        int Q = j - i + Shift;\n\
    \        if(!chts[Q].empty()) chmin(dp2[i + 1][j], S[i] * S[i] + chts[Q].query_monotone_dec(-2\
    \ * S[i]));\n      }\n    }\n    for(int j = 0; j <= N; j++) {\n      if(i) dp[i][j]\
    \ = min(dp[i - 1][j], dp2[i][j]);\n      if(dp[i][j] != infll) chts[j - i + Shift].add(S[i],\
    \ dp[i][j] + S[i] * S[i]);\n    }\n  }\n\n  for(int i = 1; i <= N; i++) {\n  \
    \  cout << dp[N + 1][i] << endl;\n  }\n}\n"
  dependsOn:
  - template/template.hpp
  - structure/convex-hull-trick/convex-hull-trick-add-monotone.hpp
  isVerificationFile: true
  path: test/verify/yukicoder-952.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yukicoder-952.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yukicoder-952.test.cpp
- /verify/test/verify/yukicoder-952.test.cpp.html
title: test/verify/yukicoder-952.test.cpp
---
