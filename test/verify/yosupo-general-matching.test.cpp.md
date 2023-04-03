---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/flow/gabow-edmonds.hpp
    title: "Gabow Edmonds(\u4E00\u822C\u30B0\u30E9\u30D5\u306E\u6700\u5927\u30DE\u30C3\
      \u30C1\u30F3\u30B0)"
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
    PROBLEM: https://judge.yosupo.jp/problem/general_matching
    links:
    - https://judge.yosupo.jp/problem/general_matching
  bundledCode: "#line 1 \"test/verify/yosupo-general-matching.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/general_matching\"\n\n#line 1 \"template/template.hpp\"\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/yosupo-general-matching.test.cpp\"\
    \n\n#line 1 \"graph/flow/gabow-edmonds.hpp\"\n// https://qiita.com/Kutimoti_T/items/5b579773e0a24d650bdf\n\
    \n/**\n * @brief Gabow Edmonds(\u4E00\u822C\u30B0\u30E9\u30D5\u306E\u6700\u5927\
    \u30DE\u30C3\u30C1\u30F3\u30B0)\n * @docs docs/gabow-edmonds.md\n */\nstruct GabowEdmonds\
    \ {\n\n  struct edge {\n    int to, idx;\n  };\n\n  vector< vector< edge > > g;\n\
    \  vector< pair< int, int > > edges;\n  vector< int > mate, label, first;\n  queue<\
    \ int > que;\n\n  GabowEdmonds(int n) : g(n + 1), mate(n + 1), label(n + 1, -1),\
    \ first(n + 1) {}\n\n  void add_edge(int u, int v) {\n    ++u, ++v;\n    g[u].push_back((edge)\
    \ {v, (int) (edges.size() + g.size())});\n    g[v].push_back((edge) {u, (int)\
    \ (edges.size() + g.size())});\n    edges.emplace_back(u, v);\n  }\n\n  int find(int\
    \ x) {\n    if(label[first[x]] < 0) return first[x];\n    first[x] = find(first[x]);\n\
    \    return first[x];\n  }\n\n  void rematch(int v, int w) {\n    int t = mate[v];\n\
    \    mate[v] = w;\n    if(mate[t] != v) return;\n    if(label[v] < (int)g.size())\
    \ {\n      mate[t] = label[v];\n      rematch(label[v], t);\n    } else {\n  \
    \    int x = edges[label[v] - g.size()].first;\n      int y = edges[label[v] -\
    \ g.size()].second;\n      rematch(x, y);\n      rematch(y, x);\n    }\n  }\n\n\
    \  void assign_label(int x, int y, int num) {\n    int r = find(x);\n    int s\
    \ = find(y);\n    int join = 0;\n    if(r == s) return;\n    label[r] = -num;\n\
    \    label[s] = -num;\n    while(true) {\n      if(s != 0) swap(r, s);\n     \
    \ r = find(label[mate[r]]);\n      if(label[r] == -num) {\n        join = r;\n\
    \        break;\n      }\n      label[r] = -num;\n    }\n    int v = first[x];\n\
    \    while(v != join) {\n      que.push(v);\n      label[v] = num;\n      first[v]\
    \ = join;\n      v = first[label[mate[v]]];\n    }\n    v = first[y];\n    while(v\
    \ != join) {\n      que.push(v);\n      label[v] = num;\n      first[v] = join;\n\
    \      v = first[label[mate[v]]];\n    }\n  }\n\n  bool augment_check(int u) {\n\
    \    que = queue< int >();\n    first[u] = 0;\n    label[u] = 0;\n    que.push(u);\n\
    \    while(!que.empty()) {\n      int x = que.front();\n      que.pop();\n   \
    \   for(auto e : g[x]) {\n        int y = e.to;\n        if(mate[y] == 0 && y\
    \ != u) {\n          mate[y] = x;\n          rematch(x, y);\n          return\
    \ true;\n        } else if(label[y] >= 0) {\n          assign_label(x, y, e.idx);\n\
    \        } else if(label[mate[y]] < 0) {\n          label[mate[y]] = x;\n    \
    \      first[mate[y]] = y;\n          que.push(mate[y]);\n        }\n      }\n\
    \    }\n    return false;\n  }\n\n  vector< pair< int, int > > max_matching()\
    \ {\n    for(int i = 1; i < (int)g.size(); i++) {\n      if(mate[i] != 0) continue;\n\
    \      if(augment_check(i)) label.assign(g.size(), -1);\n    }\n    vector< pair<\
    \ int, int > > ret;\n    for(int i = 1; i < (int)g.size(); i++) {\n      if(i\
    \ < mate[i]) ret.emplace_back(i - 1, mate[i] - 1);\n    }\n    return ret;\n \
    \ }\n};\n#line 6 \"test/verify/yosupo-general-matching.test.cpp\"\n\nint main()\
    \ {\n  int N, M;\n  cin >> N >> M;\n  GabowEdmonds flow(N);\n  for(int i = 0;\
    \ i < M; i++) {\n    int a, b;\n    cin >> a >> b;\n    flow.add_edge(a, b);\n\
    \  }\n  auto ret = flow.max_matching();\n  cout << ret.size() << endl;\n  for(auto\
    \ &p : ret) cout << p << endl;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/general_matching\"\n\n\
    #include \"../../template/template.hpp\"\n\n#include \"../../graph/flow/gabow-edmonds.hpp\"\
    \n\nint main() {\n  int N, M;\n  cin >> N >> M;\n  GabowEdmonds flow(N);\n  for(int\
    \ i = 0; i < M; i++) {\n    int a, b;\n    cin >> a >> b;\n    flow.add_edge(a,\
    \ b);\n  }\n  auto ret = flow.max_matching();\n  cout << ret.size() << endl;\n\
    \  for(auto &p : ret) cout << p << endl;\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/flow/gabow-edmonds.hpp
  isVerificationFile: true
  path: test/verify/yosupo-general-matching.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/yosupo-general-matching.test.cpp
layout: document
redirect_from:
- /verify/test/verify/yosupo-general-matching.test.cpp
- /verify/test/verify/yosupo-general-matching.test.cpp.html
title: test/verify/yosupo-general-matching.test.cpp
---
