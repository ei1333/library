---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/suffix-array.hpp
    title: "Suffix Array(\u63A5\u5C3E\u8F9E\u914D\u5217)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-number-of-substrings.test.cpp
    title: test/verify/yosupo-number-of-substrings.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: LCP Array
    links: []
  bundledCode: "#line 1 \"string/suffix-array.hpp\"\n/**\n * @brief Suffix Array(\u63A5\
    \u5C3E\u8F9E\u914D\u5217)\n */\ntemplate< typename T >\nstruct SuffixArray : vector<\
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
    ] \" << vs.substr((*this)[i]) << \"\\n\";\n  }\n}\n#line 2 \"string/lcp-array.hpp\"\
    \n\n/**\n * @brief LCP Array\n */\ntemplate< typename T >\nvector< int > lcp_array(const\
    \ SuffixArray< T > &sa) {\n  int n = (int) sa.size() - 1;\n  vector< int > lcp(n\
    \ + 1), rank(n + 1);\n  for(int i = 0; i <= n; i++) {\n    rank[sa[i]] = i;\n\
    \  }\n  int h = 0;\n  for(int i = 0; i <= n; i++) {\n    if(rank[i] < n) {\n \
    \     int j = sa[rank[i] + 1];\n      for(; j + h < n && i + h < n; h++) {\n \
    \       if(sa.vs[j + h] != sa.vs[i + h]) break;\n      }\n      lcp[rank[i] +\
    \ 1] = h;\n      if(h > 0) h--;\n    }\n  }\n  return lcp;\n}\n\n"
  code: "#include \"suffix-array.hpp\"\n\n/**\n * @brief LCP Array\n */\ntemplate<\
    \ typename T >\nvector< int > lcp_array(const SuffixArray< T > &sa) {\n  int n\
    \ = (int) sa.size() - 1;\n  vector< int > lcp(n + 1), rank(n + 1);\n  for(int\
    \ i = 0; i <= n; i++) {\n    rank[sa[i]] = i;\n  }\n  int h = 0;\n  for(int i\
    \ = 0; i <= n; i++) {\n    if(rank[i] < n) {\n      int j = sa[rank[i] + 1];\n\
    \      for(; j + h < n && i + h < n; h++) {\n        if(sa.vs[j + h] != sa.vs[i\
    \ + h]) break;\n      }\n      lcp[rank[i] + 1] = h;\n      if(h > 0) h--;\n \
    \   }\n  }\n  return lcp;\n}\n\n"
  dependsOn:
  - string/suffix-array.hpp
  isVerificationFile: false
  path: string/lcp-array.hpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-number-of-substrings.test.cpp
documentation_of: string/lcp-array.hpp
layout: document
redirect_from:
- /library/string/lcp-array.hpp
- /library/string/lcp-array.hpp.html
title: LCP Array
---
