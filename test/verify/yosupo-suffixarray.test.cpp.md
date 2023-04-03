---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/suffix-array.hpp
    title: "Suffix Array(\u63A5\u5C3E\u8F9E\u914D\u5217)"
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
    PROBLEM: https://judge.yosupo.jp/problem/suffixarray
    links:
    - https://judge.yosupo.jp/problem/suffixarray
  bundledCode: "#line 1 \"test/verify/yosupo-suffixarray.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/suffixarray\"\n\n#line 1 \"template/template.hpp\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-suffixarray.test.cpp\"\
    \n\n#line 1 \"string/suffix-array.hpp\"\n/**\n * @brief Suffix Array(\u63A5\u5C3E\
    \u8F9E\u914D\u5217)\n */\ntemplate< typename T >\nstruct SuffixArray : vector<\
    \ int > {\nprivate:\n  vector< int > sa_is(const vector< int > &s) const {\n \
    \   const int n = (int) s.size();\n    vector< int > ret(n);\n\n    vector< int\
    \ > is_s(n), is_lms(n);\n    int m = 0;\n    for(int i = n - 2; i >= 0; i--) {\n\
    \      is_s[i] = (s[i] > s[i + 1]) or (s[i] == s[i + 1] and is_s[i + 1]);\n  \
    \    m += (is_lms[i + 1] = is_s[i] and not is_s[i + 1]);\n    }\n\n    auto induced_sort\
    \ = [&](const vector< int > &lms) {\n      int upper = *max_element(s.begin(),\
    \ s.end());\n      vector< int > l(upper + 2), r(upper + 2);\n      for(auto &&v:\
    \ s) {\n        ++l[v + 1];\n        ++r[v];\n      }\n      partial_sum(l.begin(),\
    \ l.end(), l.begin());\n      partial_sum(r.begin(), r.end(), r.begin());\n  \
    \    fill(ret.begin(), ret.end(), -1);\n      for(int i = (int) lms.size() - 1;\
    \ i >= 0; i--) {\n        ret[--r[s[lms[i]]]] = lms[i];\n      }\n      for(auto\
    \ &&v: ret) {\n        if(v >= 1 and is_s[v - 1]) ret[l[s[v - 1]]++] = v - 1;\n\
    \      }\n      fill(r.begin(), r.end(), 0);\n      for(auto &&v: s) ++r[v];\n\
    \      partial_sum(r.begin(), r.end(), r.begin());\n      for(int k = (int) ret.size()\
    \ - 1, i = ret[k]; k >= 1; i = ret[--k]) {\n        if(i >= 1 and not is_s[i -\
    \ 1]) {\n          ret[--r[s[i - 1]]] = i - 1;\n        }\n      }\n    };\n\n\
    \    vector< int > lms;\n    lms.reserve(m);\n    for(int i = 1; i < n; i++) {\n\
    \      if(is_lms[i]) lms.push_back(i);\n    }\n\n    induced_sort(lms);\n\n  \
    \  vector< int > new_lms;\n    new_lms.reserve(m);\n    for(int i = 0; i < n;\
    \ i++) {\n      if(not is_s[ret[i]] and ret[i] > 0 and is_s[ret[i] - 1]) {\n \
    \       new_lms.push_back(ret[i]);\n      }\n    }\n\n    auto is_same = [&](int\
    \ a, int b) {\n      if(s[a++] != s[b++]) return false;\n      for(;; ++a, ++b)\
    \ {\n        if(s[a] != s[b]) return false;\n        if(is_lms[a] or is_lms[b])\
    \ return is_lms[a] and is_lms[b];\n      }\n    };\n\n    int rank = 0;\n    ret[n\
    \ - 1] = 0;\n    for(int i = 1; i < m; i++) {\n      if(not is_same(new_lms[i\
    \ - 1], new_lms[i])) ++rank;\n      ret[new_lms[i]] = rank;\n    }\n\n    if(rank\
    \ + 1 < m) {\n      vector< int > new_s(m);\n      for(int i = 0; i < m; i++)\
    \ {\n        new_s[i] = ret[lms[i]];\n      }\n      auto lms_sa = sa_is(new_s);\n\
    \      for(int i = 0; i < m; i++) {\n        new_lms[i] = lms[lms_sa[i]];\n  \
    \    }\n    }\n\n    induced_sort(new_lms);\n\n    return ret;\n  }\n\npublic:\n\
    \  T vs;\n\n  explicit SuffixArray(const T &vs, bool compress = false) : vs(vs)\
    \ {\n    vector< int > new_vs(vs.size() + 1);\n    if(compress) {\n      T xs\
    \ = vs;\n      sort(xs.begin(), xs.end());\n      xs.erase(unique(xs.begin(),\
    \ xs.end()), xs.end());\n      for(int i = 0; i < (int) vs.size(); i++) {\n  \
    \      new_vs[i] = std::lower_bound(xs.begin(), xs.end(), vs[i]) - xs.begin()\
    \ + 1;\n      }\n    } else {\n      auto d = *min_element(vs.begin(), vs.end());\n\
    \      for(int i = 0; i < (int) vs.size(); i++) {\n        new_vs[i] = vs[i] -\
    \ d + 1;\n      }\n    }\n    auto ret = sa_is(new_vs);\n    assign(ret.begin(),\
    \ ret.end());\n  }\n\n  void output() const {\n    for(int i = 0; i < size();\
    \ i++) {\n      cout << i << \":[\" << (*this)[i] << \"]\";\n      for(int j =\
    \ (*this)[i]; j < (int) vs.size(); j++) cout << \" \" << vs[j];\n      cout <<\
    \ \"\\n\";\n    }\n  }\n\n\n  bool lt_substr(const string &t, int si = 0, int\
    \ ti = 0) {\n    int sn = (int) vs.size(), tn = (int) t.size();\n    while(si\
    \ < sn && ti < tn) {\n      if(vs[si] < t[ti]) return true;\n      if(vs[si] >\
    \ t[ti]) return false;\n      ++si, ++ti;\n    }\n    return si >= sn && ti <\
    \ tn;\n  }\n\n  // t <= s[i,N) \u306A\u308B\u6700\u5C0F\u306E i \u3092\u8FD4\u3059\
    \ O(|t| log |s|)\n  int lower_bound(const T &t) {\n    int ng = 0, ok = (int)\
    \ size();\n    while(ok - ng > 1) {\n      int mid = (ok + ng) / 2;\n      if(lt_substr(t,\
    \ at(mid))) ng = mid;\n      else ok = mid;\n    }\n    return ok;\n  }\n\n  //\
    \ O(|t| log |s|)\n  pair< int, int > equal_range(T &t) {\n    int low = lower_bound(t);\n\
    \    int ng = low - 1, ok = (int) size();\n    t.back()++;\n    while(ok - ng\
    \ > 1) {\n      int mid = (ok + ng) / 2;\n      if(lt_substr(t, at(mid))) ng =\
    \ mid;\n      else ok = mid;\n    }\n    t.back()--;\n    return {low, ok};\n\
    \  }\n};\n\ntemplate<>\nvoid SuffixArray< string >::output() const {\n  for(int\
    \ i = 0; i < (int) size(); i++) {\n    cout << i << \":[\" << (*this)[i] << \"\
    ] \" << vs.substr((*this)[i]) << \"\\n\";\n  }\n}\n#line 6 \"test/verify/yosupo-suffixarray.test.cpp\"\
    \n\nint main() {\n  string s;\n  cin >> s;\n  auto sa = SuffixArray(s);\n  sa.erase(sa.begin());\n\
    \  cout << sa << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/suffixarray\"\n\n#include\
    \ \"../../template/template.hpp\"\n\n#include \"../../string/suffix-array.hpp\"\
    \n\nint main() {\n  string s;\n  cin >> s;\n  auto sa = SuffixArray(s);\n  sa.erase(sa.begin());\n\
    \  cout << sa << \"\\n\";\n}\n"
  dependsOn:
  - template/template.hpp
  - string/suffix-array.hpp
  isVerificationFile: true
  path: test/verify/yosupo-suffixarray.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-suffixarray.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-suffixarray.test.cpp
- /verify/test/verify/yosupo-suffixarray.test.cpp.html
title: test/verify/yosupo-suffixarray.test.cpp
---
