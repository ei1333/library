---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: dp/monotone-minima.hpp
    title: Monotone Minima
  - icon: ':heavy_check_mark:'
    path: dp/online-offline-dp.hpp
    title: "Online Offline DP(\u30AA\u30F3\u30E9\u30A4\u30F3\u30FB\u30AA\u30D5\u30E9\
      \u30A4\u30F3\u5909\u63DB)"
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
    PROBLEM: https://yukicoder.me/problems/no/705
    links:
    - https://yukicoder.me/problems/no/705
  bundledCode: "#line 1 \"test/verify/yukicoder-705.test.cpp\"\n#define PROBLEM \"\
    https://yukicoder.me/problems/no/705\"\n\n#line 1 \"template/template.hpp\"\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yukicoder-705.test.cpp\"\
    \n\n#line 1 \"dp/monotone-minima.hpp\"\ntemplate< typename T, typename Compare\
    \ = less< T > >\nvector< pair< int, T > > monotone_minima(int H, int W, const\
    \ function< T(int, int) > &f, const Compare &comp = Compare()) {\n  vector< pair<\
    \ int, T > > dp(H);\n  function< void(int, int, int, int) > dfs = [&](int top,\
    \ int bottom, int left, int right) {\n    if(top > bottom) return;\n    int line\
    \ = (top + bottom) / 2;\n    T ma;\n    int mi = -1;\n    for(int i = left; i\
    \ <= right; i++) {\n      T cst = f(line, i);\n      if(mi == -1 || comp(cst,\
    \ ma)) {\n        ma = cst;\n        mi = i;\n      }\n    }\n    dp[line] = make_pair(mi,\
    \ ma);\n    dfs(top, line - 1, left, mi);\n    dfs(line + 1, bottom, mi, right);\n\
    \  };\n  dfs(0, H - 1, 0, W - 1);\n  return dp;\n}\n#line 2 \"dp/online-offline-dp.hpp\"\
    \n\ntemplate< typename T, typename Compare = less< T > >\nvector< T > online_offline_dp(int\
    \ W, const function< T(int, int) > &f, const Compare &comp = Compare()) {\n  vector<\
    \ T > dp(W + 1);\n  vector< int > isset(W + 1);\n  int y_base = -1, x_base = -1;\n\
    \  function< T(int, int) > get_cost = [&](int y, int x) { // return dp[0, x+x_base)+f[x+x_base,\
    \ y+y_base)\n    return dp[x + x_base] + f(x + x_base, y + y_base);\n  };\n  function<\
    \ void(int, int, int) > induce = [&](int l, int m, int r) { // dp[l, m) -> dp[m,\
    \ r)\n    x_base = l, y_base = m;\n    auto ret = monotone_minima(r - m, m - l,\
    \ get_cost, comp);\n    for(int i = 0; i < ret.size(); i++) {\n      if(!isset[m\
    \ + i] || comp(ret[i].second, dp[m + i])) {\n        isset[m + i] = true;\n  \
    \      dp[m + i] = ret[i].second;\n      }\n    }\n  };\n  function< void(int,\
    \ int) > dfs = [&](int l, int r) {\n    if(l + 1 == r) {\n      x_base = l, y_base\
    \ = l;\n      T cst = l ? get_cost(0, -1) : 0;\n      if(!isset[l] || comp(cst,\
    \ dp[l])) {\n        isset[l] = true;\n        dp[l] = cst;\n      }\n    } else\
    \ {\n      int mid = (l + r) / 2;\n      dfs(l, mid);\n      induce(l, mid, r);\n\
    \      dfs(mid, r);\n    }\n  };\n  dfs(0, W + 1);\n  return dp;\n};\n#line 6\
    \ \"test/verify/yukicoder-705.test.cpp\"\n\nint main() {\n  int n;\n  cin >> n;\n\
    \  vector< int > a(n), x(n), y(n);\n  for(int i = 0; i < n; i++) cin >> a[i];\n\
    \  for(int i = 0; i < n; i++) cin >> x[i];\n  for(int i = 0; i < n; i++) cin >>\
    \ y[i];\n  function< int64_t(int, int) > dist = [&](int i, int j) {\n    assert(0\
    \ <= i && i < j && j <= n);\n    int s = abs(a[j - 1] - x[i]);\n    int t = abs(y[i]);\n\
    \    return 1LL * s * s * s + 1LL * t * t * t;\n  };\n  cout << online_offline_dp(n,\
    \ dist).back() << endl;\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/705\"\n\n#include \"../../template/template.hpp\"\
    \n\n#include \"../../dp/online-offline-dp.hpp\"\n\nint main() {\n  int n;\n  cin\
    \ >> n;\n  vector< int > a(n), x(n), y(n);\n  for(int i = 0; i < n; i++) cin >>\
    \ a[i];\n  for(int i = 0; i < n; i++) cin >> x[i];\n  for(int i = 0; i < n; i++)\
    \ cin >> y[i];\n  function< int64_t(int, int) > dist = [&](int i, int j) {\n \
    \   assert(0 <= i && i < j && j <= n);\n    int s = abs(a[j - 1] - x[i]);\n  \
    \  int t = abs(y[i]);\n    return 1LL * s * s * s + 1LL * t * t * t;\n  };\n \
    \ cout << online_offline_dp(n, dist).back() << endl;\n}\n"
  dependsOn:
  - template/template.hpp
  - dp/online-offline-dp.hpp
  - dp/monotone-minima.hpp
  isVerificationFile: true
  path: test/verify/yukicoder-705.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yukicoder-705.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yukicoder-705.test.cpp
- /verify/test/verify/yukicoder-705.test.cpp.html
title: test/verify/yukicoder-705.test.cpp
---
