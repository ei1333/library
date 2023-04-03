---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/flow/push-relabel.hpp
    title: graph/flow/push-relabel.hpp
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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A
  bundledCode: "#line 1 \"test/verify/aoj-grl-6-a-3.test.cpp\"\n#define PROBLEM \"\
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A\"\n\n#line 1\
    \ \"template/template.hpp\"\n#include<bits/stdc++.h>\n\nusing namespace std;\n\
    \nusing int64 = long long;\nconst int mod = 1e9 + 7;\n\nconst int64 infll = (1LL\
    \ << 62) - 1;\nconst int inf = (1 << 30) - 1;\n\nstruct IoSetup {\n  IoSetup()\
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
    \ MFP(F &&f) {\n  return FixPoint< F >{forward< F >(f)};\n}\n#line 4 \"test/verify/aoj-grl-6-a-3.test.cpp\"\
    \n\n#line 1 \"graph/flow/push-relabel.hpp\"\nclass Stack {\nprivate:\n  const\
    \ int N, H;\n  vector< int > node;\n \npublic:\n  Stack(const int N, const int\
    \ H) : N(N), H(H), node(N + H) { clear(); }\n \n  inline bool empty(const int\
    \ h) const { return node[N + h] == N + h; }\n \n  inline int top(const int h)\
    \ const { return node[N + h]; }\n \n  inline void pop(const int h) { node[N +\
    \ h] = node[node[N + h]]; }\n \n  inline void push(const int h, const int u) {\
    \ node[u] = node[N + h], node[N + h] = u; }\n \n  inline void clear() { iota(node.begin()\
    \ + N, node.end(), N); }\n};\n \nclass List {\npublic:\n  struct node {\n    int\
    \ prev, next;\n  };\n  const int N, H;\n  vector< node > dat;\n \n  List(const\
    \ int N, const int H) : N(N), H(H), dat(N + H) { clear(); }\n \n  inline bool\
    \ empty(const int h) const { return (dat[N + h].next == N + h); }\n \n  inline\
    \ bool more_one(const int h) const { return dat[N + h].prev != dat[N + h].next;\
    \ }\n \n  inline void insert(const int h, const int u) {\n    dat[u].prev = dat[N\
    \ + h].prev, dat[u].next = N + h;\n    dat[dat[N + h].prev].next = u, dat[N +\
    \ h].prev = u;\n  }\n \n  inline void erase(const int u) {\n    dat[dat[u].prev].next\
    \ = dat[u].next, dat[dat[u].next].prev = dat[u].prev;\n  }\n \n  inline void clear()\
    \ {\n    for(int i = N; i < N + H; ++i) dat[i].prev = dat[i].next = i;\n  }\n\
    };\n\ntemplate< typename flow_t >\nstruct PushRelabel {\n  struct edge {\n   \
    \ int to;\n    flow_t cap;\n    int rev;\n    bool isrev;\n    int idx;\n  };\n\
    \n  int V, height, relabels;\n  vector< flow_t > ex;\n  vector< int > potential,\
    \ cur_edge;\n  List all_ver;\n  Stack act_ver;\n  vector< vector< edge > > graph;\n\
    \n  PushRelabel(int V)\n      : V(V), height(-1), relabels(0), ex(V, flow_t(0)),\
    \ potential(V, 0), cur_edge(V), all_ver(V, V), act_ver(V, V), graph(V) {}\n\n\
    \  void add_edge(int from, int to, flow_t cap, int idx = -1) {\n    graph[from].emplace_back((edge)\
    \ {to, cap, (int) graph[to].size(), false, idx});\n    graph[to].emplace_back((edge)\
    \ {from, 0, (int) graph[from].size() - 1, true, idx});\n  }\n\n  int calc_active(int\
    \ t) {\n    height = -1;\n    for(int i = 0; i < V; i++) {\n      if(potential[i]\
    \ < V) {\n        cur_edge[i] = 0;\n        height = max(height, potential[i]);\n\
    \        all_ver.insert(potential[i], i);\n        if(ex[i] > 0 && i != t) act_ver.push(potential[i],\
    \ i);\n      } else {\n        potential[i] = V + 1;\n      }\n    }\n    return\
    \ height;\n  }\n\n  void bfs(int t) {\n    for(int i = 0; i < V; i++) {\n    \
    \  potential[i] = max(potential[i], V);\n    }\n    potential[t] = 0;\n    queue<\
    \ int > que;\n    que.emplace(t);\n    while(!que.empty()) {\n      int p = que.front();\n\
    \      que.pop();\n      for(auto &e : graph[p]) {\n        if(potential[e.to]\
    \ == V && graph[e.to][e.rev].cap > 0) {\n          potential[e.to] = potential[p]\
    \ + 1;\n          que.emplace(e.to);\n        }\n      }\n    }\n  }\n\n  int\
    \ init(int s, int t) {\n    potential[s] = V + 1;\n    bfs(t);\n    for(auto &e\
    \ : graph[s]) {\n      if(potential[e.to] < V) {\n        graph[e.to][e.rev].cap\
    \ = e.cap;\n        ex[s] -= e.cap;\n        ex[e.to] += e.cap;\n      }\n   \
    \   e.cap = 0;\n    }\n    return calc_active(t);\n  }\n\n  bool push(int u, int\
    \ t, edge &e) {\n    flow_t f = min(e.cap, ex[u]);\n    int v = e.to;\n    e.cap\
    \ -= f, ex[u] -= f;\n    graph[v][e.rev].cap += f, ex[v] += f;\n    if(ex[v] ==\
    \ f && v != t) act_ver.push(potential[v], v);\n    return ex[u] == 0;\n  }\n\n\
    \  int discharge(int u, int t) {\n    for(int &i = cur_edge[u]; i < (int)graph[u].size();\
    \ i++) {\n      auto &e = graph[u][i];\n      if(potential[u] == potential[e.to]\
    \ + 1 && e.cap > 0) {\n        if(push(u, t, e)) return potential[u];\n      }\n\
    \    }\n    return relabel(u);\n  }\n\n  int global_relabel(int t) {\n    bfs(t);\n\
    \    all_ver.clear(), act_ver.clear();\n    return calc_active(t);\n  }\n\n  void\
    \ gap_relabel(const int u) {\n    for(int i = potential[u]; i <= height; ++i)\
    \ {\n      for(int id = all_ver.dat[V + i].next; id < V; id = all_ver.dat[id].next)\
    \ {\n        potential[id] = V + 1;\n      }\n      all_ver.dat[V + i].prev =\
    \ all_ver.dat[V + i].next = V + i;\n    }\n  }\n\n  int relabel(const int u) {\n\
    \    ++relabels;\n    int prv = potential[u], cur = V;\n    for(int i = 0; i <\
    \ (int) graph[u].size(); ++i) {\n      const edge &e = graph[u][i];\n      if(cur\
    \ > potential[e.to] + 1 && e.cap > 0) {\n        cur_edge[u] = i;\n        cur\
    \ = potential[e.to] + 1;\n      }\n    }\n    if(all_ver.more_one(prv)) {\n  \
    \    all_ver.erase(u);\n      if((potential[u] = cur) == V) return potential[u]\
    \ = V + 1, prv;\n      act_ver.push(cur, u);\n      all_ver.insert(cur, u);\n\
    \      height = max(height, cur);\n    } else {\n      gap_relabel(u);\n     \
    \ return height = prv - 1;\n    }\n    return cur;\n  }\n\n  flow_t max_flow(int\
    \ s, int t) {\n    int level = init(s, t);\n    while(level >= 0) {\n      if(act_ver.empty(level))\
    \ {\n        --level;\n        continue;\n      }\n      int u = act_ver.top(level);\n\
    \      act_ver.pop(level);\n      level = discharge(u, t);\n      if(relabels\
    \ * 2 >= V) {\n        level = global_relabel(t);\n        relabels = 0;\n   \
    \   }\n    }\n    return ex[t];\n  }\n};\n#line 6 \"test/verify/aoj-grl-6-a-3.test.cpp\"\
    \n\nint main() {\n  int V, E;\n  scanf(\"%d %d\", &V, &E);\n  PushRelabel< int\
    \ > g(V);\n  for(int i = 0; i < E; i++) {\n    int a, b, c;\n    scanf(\"%d %d\
    \ %d\", &a, &b, &c);\n    g.add_edge(a, b, c);\n  }\n  printf(\"%d\\n\", g.max_flow(0,\
    \ V - 1));\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A\"\
    \n\n#include \"../../template/template.hpp\"\n\n#include \"../../graph/flow/push-relabel.hpp\"\
    \n\nint main() {\n  int V, E;\n  scanf(\"%d %d\", &V, &E);\n  PushRelabel< int\
    \ > g(V);\n  for(int i = 0; i < E; i++) {\n    int a, b, c;\n    scanf(\"%d %d\
    \ %d\", &a, &b, &c);\n    g.add_edge(a, b, c);\n  }\n  printf(\"%d\\n\", g.max_flow(0,\
    \ V - 1));\n}\n"
  dependsOn:
  - template/template.hpp
  - graph/flow/push-relabel.hpp
  isVerificationFile: true
  path: test/verify/aoj-grl-6-a-3.test.cpp
  requiredBy: []
  timestamp: '2022-09-11 00:53:50+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/verify/aoj-grl-6-a-3.test.cpp
layout: document
redirect_from:
- /verify/test/verify/aoj-grl-6-a-3.test.cpp
- /verify/test/verify/aoj-grl-6-a-3.test.cpp.html
title: test/verify/aoj-grl-6-a-3.test.cpp
---
