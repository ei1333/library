---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: dp/edit-distance.hpp
    title: "Edit Distance(\u7DE8\u96C6\u8DDD\u96E2)"
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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_E
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_E
  bundledCode: "#line 1 \"test/verify/aoj-dpl-1-e.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_E\"\
    \n\n#line 1 \"template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-dpl-1-e.test.cpp\"\
    \n\n#line 1 \"dp/edit-distance.hpp\"\nint edit_distance(const string &S, const\
    \ string &T) {\n  const int N = (int) S.size(), M = (int) T.size();\n  vector<\
    \ vector< int > > dp(N + 1, vector< int >(M + 1, N + M));\n  for(int i = 0; i\
    \ <= N; i++) dp[i][0] = i;\n  for(int i = 0; i <= M; i++) dp[0][i] = i;\n  for(int\
    \ i = 1; i <= N; i++) {\n    for(int j = 1; j <= M; j++) {\n      dp[i][j] = min(dp[i][j],\
    \ dp[i - 1][j] + 1);\n      dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);\n    \
    \  dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + (S[i - 1] != T[j - 1]));\n    }\n\
    \  }\n  return dp[N][M];\n}\n#line 6 \"test/verify/aoj-dpl-1-e.test.cpp\"\n\n\
    int main() {\n  string S, T;\n  cin >> S >> T;\n  cout << edit_distance(S, T)\
    \ << endl;\n}\n\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_E\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../dp/edit-distance.hpp\"\
    \n\nint main() {\n  string S, T;\n  cin >> S >> T;\n  cout << edit_distance(S,\
    \ T) << endl;\n}\n\n"
  dependsOn:
  - template/template.hpp
  - dp/edit-distance.hpp
  isVerificationFile: true
  path: test/verify/aoj-dpl-1-e.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-dpl-1-e.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-dpl-1-e.test.cpp
- /verify/test/verify/aoj-dpl-1-e.test.cpp.html
title: test/verify/aoj-dpl-1-e.test.cpp
---
