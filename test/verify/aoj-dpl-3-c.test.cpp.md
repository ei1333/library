---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: dp/largest-rectangle.hpp
    title: "Largest Rectangle(\u6700\u5927\u9577\u65B9\u5F62)"
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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_3_C
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_3_C
  bundledCode: "#line 1 \"test/verify/aoj-dpl-3-c.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_3_C\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-dpl-3-c.test.cpp\"\
    \n\n#line 1 \"dp/largest-rectangle.hpp\"\ntemplate< typename T >\nint64_t largest_rectangle(vector<\
    \ T > height)\n{\n  stack< int > st;\n  height.push_back(0);\n  vector< int >\
    \ left(height.size());\n  int64_t ret = 0;\n  for(int i = 0; i < height.size();\
    \ i++) {\n    while(!st.empty() && height[st.top()] >= height[i]) {\n      ret\
    \ = max(ret, (int64_t) (i - left[st.top()] - 1) * height[st.top()]);\n      st.pop();\n\
    \    }\n    left[i] = st.empty() ? -1 : st.top();\n    st.emplace(i);\n  }\n \
    \ return (ret);\n}\n#line 6 \"test/verify/aoj-dpl-3-c.test.cpp\"\n\nint main()\
    \ {\n  int N;\n  cin >> N;\n  vector< int > h(N);\n  cin >> h;\n  cout << largest_rectangle(h)\
    \ << endl;\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_3_C\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../dp/largest-rectangle.hpp\"\
    \n\nint main() {\n  int N;\n  cin >> N;\n  vector< int > h(N);\n  cin >> h;\n\
    \  cout << largest_rectangle(h) << endl;\n}\n"
  dependsOn:
  - template/template.hpp
  - dp/largest-rectangle.hpp
  isVerificationFile: true
  path: test/verify/aoj-dpl-3-c.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-dpl-3-c.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-dpl-3-c.test.cpp
- /verify/test/verify/aoj-dpl-3-c.test.cpp.html
title: test/verify/aoj-dpl-3-c.test.cpp
---
