---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/z-algorithm.hpp
    title: Z Algorithm
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
    PROBLEM: https://judge.yosupo.jp/problem/zalgorithm
    links:
    - https://judge.yosupo.jp/problem/zalgorithm
  bundledCode: "#line 1 \"test/verify/yosupo-zalgorithm.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/zalgorithm\"\n\n#line 1 \"template/template.hpp\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-zalgorithm.test.cpp\"\
    \n\n#line 1 \"string/z-algorithm.hpp\"\n/**\n * @brief Z Algorithm\n * @see https://heno239.hatenablog.com/entry/2020/07/07/140651\n\
    \ * @docs docs/z-algorithm.md\n */\ntemplate< typename T = char >\nstruct ZAlgorithm\
    \ {\nprivate:\n  vector< T > s;\n  vector< int > deleted;\n  vector< vector< int\
    \ > > delete_hist;\n  vector< int > z;\n  queue< int > cur;\npublic:\n  ZAlgorithm()\
    \ : delete_hist{{}} {}\n\n  template< typename S >\n  ZAlgorithm(const S &s) :\
    \ ZAlgorithm() {\n    for(auto &c: s) add(c);\n  }\n\n  void add(const T &c) {\n\
    \    s.emplace_back(c);\n    delete_hist.emplace_back();\n    deleted.emplace_back(0);\n\
    \    z.emplace_back(0);\n    z[0]++;\n\n    int len = (int) s.size();\n    if(len\
    \ == 1) return;\n    if(s[0] == c) cur.emplace(len - 1);\n    else deleted[len\
    \ - 1] = 1;\n\n    auto set = [&](int t, int len) {\n      deleted[t] = 1;\n \
    \     delete_hist[len].emplace_back(t);\n      z[t] = len - t - 1;\n    };\n\n\
    \    while(not cur.empty()) {\n      int t = cur.front();\n      if(deleted[t])\
    \ {\n        cur.pop();\n      } else if(s[len - t - 1] == s.back()) {\n     \
    \   break;\n      } else {\n        set(t, len);\n        cur.pop();\n      }\n\
    \    }\n\n    if(not cur.empty()) {\n      int t = cur.front();\n      for(auto\
    \ &p: delete_hist[len - t]) {\n        set(p + t, len);\n      }\n    }\n  }\n\
    \n  int get(int k) const {\n    return deleted[k] ? z[k] : (int) s.size() - k;\n\
    \  }\n\n  int operator[](int k) const {\n    return get(k);\n  }\n\n  vector<\
    \ int > get() {\n    vector< int > ret(s.size());\n    for(int i = 0; i < (int)\
    \ s.size(); i++) {\n      ret[i] = get(i);\n    }\n    return ret;\n  }\n};\n\
    #line 6 \"test/verify/yosupo-zalgorithm.test.cpp\"\n\nint main() {\n  string s;\n\
    \  cin >> s;\n  cout << ZAlgorithm(s).get() << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/zalgorithm\"\n\n#include\
    \ \"../../template/template.hpp\"\n\n#include \"../../string/z-algorithm.hpp\"\
    \n\nint main() {\n  string s;\n  cin >> s;\n  cout << ZAlgorithm(s).get() << \"\
    \\n\";\n}\n"
  dependsOn:
  - template/template.hpp
  - string/z-algorithm.hpp
  isVerificationFile: true
  path: test/verify/yosupo-zalgorithm.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-zalgorithm.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-zalgorithm.test.cpp
- /verify/test/verify/yosupo-zalgorithm.test.cpp.html
title: test/verify/yosupo-zalgorithm.test.cpp
---
