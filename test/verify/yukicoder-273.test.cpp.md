---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/palindromic-tree.hpp
    title: "Palindromic Tree(\u56DE\u6587\u6728)"
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
    PROBLEM: https://yukicoder.me/problems/no/273
    links:
    - https://yukicoder.me/problems/no/273
  bundledCode: "#line 1 \"test/verify/yukicoder-273.test.cpp\"\n#define PROBLEM \"\
    https://yukicoder.me/problems/no/273\"\n\n#line 1 \"template/template.hpp\"\n\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yukicoder-273.test.cpp\"\
    \n\n#line 1 \"string/palindromic-tree.hpp\"\n/**\n * @brief Palindromic Tree(\u56DE\
    \u6587\u6728)\n * @see https://math314.hateblo.jp/entry/2016/12/19/005919\n *\
    \ @docs docs/palindromic-tree.md\n */\ntemplate< typename T = char >\nstruct PalindromicTree\
    \ {\npublic:\n  struct Node {\n    map< T, int > link; // \u5B50\u306Eidx\n  \
    \  int suffix_link; // \u6700\u9577\u56DE\u6587\u63A5\u5C3E\u8F9E\u306Eidx\n \
    \   int len; // \u5BFE\u5FDC\u3059\u308B\u56DE\u6587\u306E\u9577\u3055\n    vector<\
    \ int > idx; // \u5BFE\u5FDC\u3059\u308B\u56DE\u6587\u3092\u6700\u9577\u56DE\u6587\
    \u63A5\u5C3E\u8F9E\u3068\u3059\u308Bidx\n    int delta_link; // \u5DEE\u5206\u304C\
    \u7570\u306A\u308B\u6700\u9577\u56DE\u6587\u63A5\u5C3E\u8F9E\u306Eidx\n\n    Node()\
    \ = default;\n\n    Node(int suf, int len) : suffix_link(suf), len(len), delta_link(-1)\
    \ {}\n  };\n\n  vector< Node > ns;\n  int ptr;\n  vector< T > vs;\n\nprivate:\n\
    \  int find_prev_palindrome(int cur) const {\n    int pos = (int) vs.size() -\
    \ 1;\n    for(;;) {\n      int rev = pos - 1 - ns[cur].len;\n      if(rev >= 0\
    \ and vs[rev] == vs.back()) break;\n      cur = ns[cur].suffix_link;\n    }\n\
    \    return cur;\n  }\n\n  bool output_dfs(int v, int id, vector< T > &ret) const\
    \ {\n    if(v == id) return true;\n    for(auto &nxt: ns[v].link) {\n      if(output_dfs(nxt.second,\
    \ id, ret)) {\n        ret.emplace_back(nxt.first);\n        return true;\n  \
    \    }\n    }\n    return false;\n  }\n\npublic:\n  PalindromicTree() : ptr(0)\
    \ {\n    ns.emplace_back(0, -1); // \u9577\u3055 -1\n    ns.emplace_back(0, 0);\
    \ // \u9577\u3055 0\n  }\n\n  PalindromicTree(const string &S) : PalindromicTree()\
    \ {\n    add(S);\n  }\n\n  int diff(int t) const {\n    if(ns[t].suffix_link <=\
    \ 0) return -1;\n    return ns[t].len - ns[ns[t].suffix_link].len;\n  }\n\n  int\
    \ add(const T &x) {\n    int idx = (int) vs.size();\n    vs.emplace_back(x);\n\
    \    int cur = find_prev_palindrome(ptr);\n    auto res = ns[cur].link.insert(make_pair(x,\
    \ (int) ns.size()));\n    ptr = res.first->second;\n    if(res.second) {\n   \
    \   ns.emplace_back(-1, ns[cur].len + 2);\n      if(ns.back().len == 1) {\n  \
    \      ns.back().suffix_link = 1;\n      } else {\n        ns.back().suffix_link\
    \ = ns[find_prev_palindrome(ns[cur].suffix_link)].link[x];\n      }\n      if(diff(ptr)\
    \ == diff(ns.back().suffix_link)) {\n        ns.back().delta_link = ns[ns.back().suffix_link].delta_link;\n\
    \      } else {\n        ns.back().delta_link = ns.back().suffix_link;\n     \
    \ }\n    }\n    ns[ptr].idx.emplace_back(idx);\n    return ptr;\n  }\n\n  // add(x)\
    \ \u306E\u3042\u3068\u306B\u547C\u3073\u51FA\u3059\n  // * init(node_idx, pos):\
    \   \u9802\u70B9 node_idx \u3092 S[pos,i] \u304C\u56DE\u6587\u306E\u3068\u304D\
    \u306E\u521D\u671F\u5024\u306B\u3059\u308B\n  // * apply(node_idx, pre_idx): \u9802\
    \u70B9 node_idx \u306B \u9802\u70B9 pre_idx \u306E\u7D50\u679C\u3092\u52A0\u3048\
    \u308B\n  // * update: S[i]\u3092\u672B\u5C3E\u3068\u3059\u308B\u56DE\u6587\u306E\
    \u9802\u70B9\u756A\u53F7\u306E\u96C6\u5408\n  template< typename I, typename U\
    \ >\n  vector< int > update_dp(const I &init, const U &apply) {\n    int i = (int)\
    \ vs.size() - 1;\n    int id = ptr;\n    vector< int > update;\n    while(ns[id].len\
    \ > 0) {\n      init(id, i + 1 - ns[ns[id].delta_link].len - diff(id));\n    \
    \  if(ns[id].suffix_link != ns[id].delta_link) {\n        apply(id, ns[id].suffix_link);\n\
    \      }\n      update.emplace_back(id);\n      id = ns[id].delta_link;\n    }\n\
    \    return update;\n  }\n\n  void add(const string &s) {\n    for(auto &x: s)\
    \ add(x);\n  }\n\n  vector< int > build_frequency() const {\n    vector< int >\
    \ ret(ns.size());\n    for(int i = (int) ns.size() - 1; i > 0; i--) {\n      ret[i]\
    \ += (int) ns[i].idx.size();\n      ret[ns[i].suffix_link] += ret[i];\n    }\n\
    \    return ret;\n  }\n\n  vector< T > output(int idx) const {\n    if(idx ==\
    \ 0) return {-1};\n    if(idx == 1) return {0};\n    vector< T > ret;\n    output_dfs(0,\
    \ idx, ret);\n    output_dfs(1, idx, ret);\n    int start = (int) ret.size() -\
    \ 1;\n    if(ns[idx].len & 1) --start;\n    for(int i = start; i >= 0; i--) {\n\
    \      ret.emplace_back(ret[i]);\n    }\n    return ret;\n  }\n\n  int size()\
    \ const {\n    return (int) ns.size();\n  }\n\n  Node &operator[](int idx) {\n\
    \    return ns[idx];\n  }\n};\n#line 6 \"test/verify/yukicoder-273.test.cpp\"\n\
    \nint main() {\n  string S;\n  cin >> S;\n  int N = (int) S.size();\n  vector<\
    \ int > dp1(N + 3, -inf), dp2(N + 1, -inf);\n  PalindromicTree t;\n  dp2[0] =\
    \ 1;\n  for(int i = 0; i < N; i++) {\n    int id = t.add(S[i]);\n    auto ret\
    \ = t.update_dp([&](int id, int pos) {\n                             if(i + 1\
    \ - pos == N) dp1[id] = dp2[pos];\n                             else dp1[id] =\
    \ max(dp2[pos], i + 1 - pos);\n                           },\n               \
    \            [&](int id, int par) {\n                             if(t[id].len\
    \ == N) chmax(dp1[id], dp1[par]);\n                             else chmax(dp1[id],\
    \ max(dp1[par], t[id].len));\n                           });\n    for(auto &p:\
    \ ret) chmax(dp2[i + 1], dp1[p]);\n  }\n  cout << dp2[N] << \"\\n\";\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/273\"\n\n#include \"../../template/template.hpp\"\
    \n\n#include \"../../string/palindromic-tree.hpp\"\n\nint main() {\n  string S;\n\
    \  cin >> S;\n  int N = (int) S.size();\n  vector< int > dp1(N + 3, -inf), dp2(N\
    \ + 1, -inf);\n  PalindromicTree t;\n  dp2[0] = 1;\n  for(int i = 0; i < N; i++)\
    \ {\n    int id = t.add(S[i]);\n    auto ret = t.update_dp([&](int id, int pos)\
    \ {\n                             if(i + 1 - pos == N) dp1[id] = dp2[pos];\n \
    \                            else dp1[id] = max(dp2[pos], i + 1 - pos);\n    \
    \                       },\n                           [&](int id, int par) {\n\
    \                             if(t[id].len == N) chmax(dp1[id], dp1[par]);\n \
    \                            else chmax(dp1[id], max(dp1[par], t[id].len));\n\
    \                           });\n    for(auto &p: ret) chmax(dp2[i + 1], dp1[p]);\n\
    \  }\n  cout << dp2[N] << \"\\n\";\n}\n"
  dependsOn:
  - template/template.hpp
  - string/palindromic-tree.hpp
  isVerificationFile: true
  path: test/verify/yukicoder-273.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yukicoder-273.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yukicoder-273.test.cpp
- /verify/test/verify/yukicoder-273.test.cpp.html
title: test/verify/yukicoder-273.test.cpp
---
