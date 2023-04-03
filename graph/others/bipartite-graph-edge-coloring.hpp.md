---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/flow/bipartite-flow.hpp
    title: "Bipartite Flow(\u4E8C\u90E8\u30B0\u30E9\u30D5\u306E\u30D5\u30ED\u30FC)"
  - icon: ':heavy_check_mark:'
    path: graph/others/eulerian-trail.hpp
    title: "Eulerian Trail(\u30AA\u30A4\u30E9\u30FC\u8DEF)"
  - icon: ':heavy_check_mark:'
    path: structure/union-find/union-find.hpp
    title: Union Find
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/verify/yosupo-bipartite-edge-coloring.test.cpp
    title: test/verify/yosupo-bipartite-edge-coloring.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/bipartite-graph-edge-coloring.md
    document_title: "Bipartite Graph Edge Coloring(\u4E8C\u90E8\u30B0\u30E9\u30D5\u306E\
      \u8FBA\u5F69\u8272)"
    links:
    - https://ei1333.hateblo.jp/entry/2020/08/25/015955
  bundledCode: "#line 2 \"graph/others/bipartite-graph-edge-coloring.hpp\"\n\n#line\
    \ 2 \"structure/union-find/union-find.hpp\"\n\nstruct UnionFind {\n  vector< int\
    \ > data;\n\n  UnionFind() = default;\n\n  explicit UnionFind(size_t sz) : data(sz,\
    \ -1) {}\n\n  bool unite(int x, int y) {\n    x = find(x), y = find(y);\n    if(x\
    \ == y) return false;\n    if(data[x] > data[y]) swap(x, y);\n    data[x] += data[y];\n\
    \    data[y] = x;\n    return true;\n  }\n\n  int find(int k) {\n    if(data[k]\
    \ < 0) return (k);\n    return data[k] = find(data[k]);\n  }\n\n  int size(int\
    \ k) {\n    return -data[find(k)];\n  }\n\n  bool same(int x, int y) {\n    return\
    \ find(x) == find(y);\n  }\n\n  vector< vector< int > > groups() {\n    int n\
    \ = (int) data.size();\n    vector< vector< int > > ret(n);\n    for(int i = 0;\
    \ i < n; i++) {\n      ret[find(i)].emplace_back(i);\n    }\n    ret.erase(remove_if(begin(ret),\
    \ end(ret), [&](const vector< int > &v) {\n      return v.empty();\n    }), end(ret));\n\
    \    return ret;\n  }\n};\n#line 1 \"graph/flow/bipartite-flow.hpp\"\n/**\n *\
    \ @brief Bipartite Flow(\u4E8C\u90E8\u30B0\u30E9\u30D5\u306E\u30D5\u30ED\u30FC\
    )\n * @docs docs/bipartite-flow.md\n */\nstruct BipartiteFlow {\n  size_t n, m,\
    \ time_stamp;\n  vector< vector< int > > g, rg;\n  vector< int > match_l, match_r,\
    \ dist, used, alive;\n  bool matched;\n\npublic:\n  explicit BipartiteFlow(size_t\
    \ n, size_t m) :\n      n(n), m(m), time_stamp(0), g(n), rg(m), match_l(n, -1),\
    \ match_r(m, -1), used(n), alive(n, 1), matched(false) {}\n\n  void add_edge(int\
    \ u, int v) {\n    g[u].push_back(v);\n    rg[v].emplace_back(u);\n  }\n\n  vector<\
    \ pair< int, int > > max_matching() {\n    matched = true;\n    for(;;) {\n  \
    \    build_augment_path();\n      ++time_stamp;\n      int flow = 0;\n      for(int\
    \ i = 0; i < (int)n; i++) {\n        if(match_l[i] == -1) flow += find_min_dist_augment_path(i);\n\
    \      }\n      if(flow == 0) break;\n    }\n    vector< pair< int, int > > ret;\n\
    \    for(int i = 0; i < (int)n; i++) {\n      if(match_l[i] >= 0) ret.emplace_back(i,\
    \ match_l[i]);\n    }\n    return ret;\n  }\n\n  /* http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3198\
    \ */\n  void erase_edge(int a, int b) {\n    if(match_l[a] == b) {\n      match_l[a]\
    \ = -1;\n      match_r[b] = -1;\n    }\n    g[a].erase(find(begin(g[a]), end(g[a]),\
    \ b));\n    rg[b].erase(find(begin(rg[b]), end(rg[b]), a));\n  }\n\n  /* http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0334\
    \ */\n  vector< pair< int, int > > lex_max_matching() {\n    if(!matched) max_matching();\n\
    \    for(auto &vs : g) sort(begin(vs), end(vs));\n    vector< pair< int, int >\
    \ > es;\n    for(int i = 0; i < (int)n; i++) {\n      if(match_l[i] == -1 || alive[i]\
    \ == 0) {\n        continue;\n      }\n      match_r[match_l[i]] = -1;\n     \
    \ match_l[i] = -1;\n      ++time_stamp;\n      find_augment_path(i);\n      alive[i]\
    \ = 0;\n      es.emplace_back(i, match_l[i]);\n    }\n    return es;\n  }\n\n\
    \  vector< int > min_vertex_cover() {\n    auto visited = find_residual_path();\n\
    \    vector< int > ret;\n    for(int i = 0; i < (int)(n + m); i++) {\n      if(visited[i]\
    \ ^ (i < (int)n)) {\n        ret.emplace_back(i);\n      }\n    }\n    return\
    \ ret;\n  }\n\n  /* https://atcoder.jp/contests/utpc2013/tasks/utpc2013_11 */\n\
    \  vector< int > lex_min_vertex_cover(const vector< int > &ord) {\n    assert(ord.size()\
    \ == n + m);\n    auto res = build_risidual_graph();\n    vector< vector< int\
    \ > > r_res(n + m + 2);\n    for(int i = 0; i < (int)(n + m + 2); i++) {\n   \
    \   for(auto &j : res[i]) r_res[j].emplace_back(i);\n    }\n    queue< int > que;\n\
    \    vector< int > visited(n + m + 2, -1);\n    auto expand_left = [&](int t)\
    \ {\n      if(visited[t] != -1) return;\n      que.emplace(t);\n      visited[t]\
    \ = 1;\n      while(!que.empty()) {\n        int idx = que.front();\n        que.pop();\n\
    \        for(auto &to : r_res[idx]) {\n          if(visited[to] != -1) continue;\n\
    \          visited[to] = 1;\n          que.emplace(to);\n        }\n      }\n\
    \    };\n    auto expand_right = [&](int t) {\n      if(visited[t] != -1) return;\n\
    \      que.emplace(t);\n      visited[t] = 0;\n      while(!que.empty()) {\n \
    \       int idx = que.front();\n        que.pop();\n        for(auto &to : res[idx])\
    \ {\n          if(visited[to] != -1) continue;\n          visited[to] = 0;\n \
    \         que.emplace(to);\n        }\n      }\n    };\n    expand_right(n + m);\n\
    \    expand_left(n + m + 1);\n    vector< int > ret;\n    for(auto &t : ord) {\n\
    \      if(t < (int)n) {\n        expand_left(t);\n        if(visited[t] & 1) ret.emplace_back(t);\n\
    \      } else {\n        expand_right(t);\n        if(~visited[t] & 1) ret.emplace_back(t);\n\
    \      }\n    }\n    return ret;\n  }\n\n\n  vector< int > max_independent_set()\
    \ {\n    auto visited = find_residual_path();\n    vector< int > ret;\n    for(int\
    \ i = 0; i < (int)(n + m); i++) {\n      if(visited[i] ^ (i >= (int)n)) {\n  \
    \      ret.emplace_back(i);\n      }\n    }\n    return ret;\n  }\n\n  vector<\
    \ pair< int, int > > min_edge_cover() {\n    auto es = max_matching();\n    for(int\
    \ i = 0; i < (int)n; i++) {\n      if(match_l[i] >= 0) {\n        continue;\n\
    \      }\n      if(g[i].empty()) {\n        return {};\n      }\n      es.emplace_back(i,\
    \ g[i][0]);\n    }\n    for(int i = 0; i < (int)m; i++) {\n      if(match_r[i]\
    \ >= 0) {\n        continue;\n      }\n      if(rg[i].empty()) {\n        return\
    \ {};\n      }\n      es.emplace_back(rg[i][0], i);\n    }\n    return es;\n \
    \ }\n\n  // left: [0,n), right: [n,n+m), S: n+m, T: n+m+1\n  vector< vector< int\
    \ > > build_risidual_graph() {\n    if(!matched) max_matching();\n    const size_t\
    \ S = n + m;\n    const size_t T = n + m + 1;\n    vector< vector< int > > ris(n\
    \ + m + 2);\n    for(int i = 0; i < (int)n; i++) {\n      if(match_l[i] == -1)\
    \ ris[S].emplace_back(i);\n      else ris[i].emplace_back(S);\n    }\n    for(int\
    \ i = 0; i < (int)m; i++) {\n      if(match_r[i] == -1) ris[i + n].emplace_back(T);\n\
    \      else ris[T].emplace_back(i + n);\n    }\n    for(int i = 0; i < (int)n;\
    \ i++) {\n      for(auto &j : g[i]) {\n        if(match_l[i] == j) ris[j + n].emplace_back(i);\n\
    \        else ris[i].emplace_back(j + n);\n      }\n    }\n    return ris;\n \
    \ }\n\nprivate:\n  vector< int > find_residual_path() {\n    auto res = build_risidual_graph();\n\
    \    queue< int > que;\n    vector< int > visited(n + m + 2);\n    que.emplace(n\
    \ + m);\n    visited[n + m] = true;\n    while(!que.empty()) {\n      int idx\
    \ = que.front();\n      que.pop();\n      for(auto &to : res[idx]) {\n       \
    \ if(visited[to]) continue;\n        visited[to] = true;\n        que.emplace(to);\n\
    \      }\n    }\n    return visited;\n  }\n\n  void build_augment_path() {\n \
    \   queue< int > que;\n    dist.assign(g.size(), -1);\n    for(int i = 0; i <\
    \ (int)n; i++) {\n      if(match_l[i] == -1) {\n        que.emplace(i);\n    \
    \    dist[i] = 0;\n      }\n    }\n    while(!que.empty()) {\n      int a = que.front();\n\
    \      que.pop();\n      for(auto &b : g[a]) {\n        int c = match_r[b];\n\
    \        if(c >= 0 && dist[c] == -1) {\n          dist[c] = dist[a] + 1;\n   \
    \       que.emplace(c);\n        }\n      }\n    }\n  }\n\n  bool find_min_dist_augment_path(int\
    \ a) {\n    used[a] = time_stamp;\n    for(auto &b : g[a]) {\n      int c = match_r[b];\n\
    \      if(c < 0 || (used[c] != (int)time_stamp && dist[c] == dist[a] + 1 && find_min_dist_augment_path(c)))\
    \ {\n        match_r[b] = a;\n        match_l[a] = b;\n        return true;\n\
    \      }\n    }\n    return false;\n  }\n\n  bool find_augment_path(int a) {\n\
    \    used[a] = time_stamp;\n    for(auto &b : g[a]) {\n      int c = match_r[b];\n\
    \      if(c < 0 || (alive[c] == 1 && used[c] != (int)time_stamp && find_augment_path(c)))\
    \ {\n        match_r[b] = a;\n        match_l[a] = b;\n        return true;\n\
    \      }\n    }\n    return false;\n  }\n};\n#line 2 \"graph/others/eulerian-trail.hpp\"\
    \n\n#line 4 \"graph/others/eulerian-trail.hpp\"\n\n/**\n * @brief Eulerian Trail(\u30AA\
    \u30A4\u30E9\u30FC\u8DEF)\n * @docs docs/eulerian-trail.md\n */\ntemplate< bool\
    \ directed >\nstruct EulerianTrail {\n  vector< vector< pair< int, int > > > g;\n\
    \  vector< pair< int, int > > es;\n  int M;\n  vector< int > used_vertex, used_edge,\
    \ deg;\n\n  explicit EulerianTrail(int V) : g(V), M(0), used_vertex(V), deg(V)\
    \ {}\n\n  void add_edge(int a, int b) {\n    es.emplace_back(a, b);\n    g[a].emplace_back(b,\
    \ M);\n    if(directed) {\n      deg[a]++;\n      deg[b]--;\n    } else {\n  \
    \    g[b].emplace_back(a, M);\n      deg[a]++;\n      deg[b]++;\n    }\n    M++;\n\
    \  }\n\n  pair< int, int > get_edge(int idx) const {\n    return es[idx];\n  }\n\
    \n  vector< vector< int > > enumerate_eulerian_trail() {\n    if(directed) {\n\
    \      for(auto &p : deg) if(p != 0) return {};\n    } else {\n      for(auto\
    \ &p : deg) if(p & 1) return {};\n    }\n    used_edge.assign(M, 0);\n    vector<\
    \ vector< int > > ret;\n    for(int i = 0; i < (int) g.size(); i++) {\n      if(g[i].empty()\
    \ || used_vertex[i]) continue;\n      ret.emplace_back(go(i));\n    }\n    return\
    \ ret;\n  }\n\n  vector< vector< int > > enumerate_semi_eulerian_trail() {\n \
    \   UnionFind uf(g.size());\n    for(auto &p : es) uf.unite(p.first, p.second);\n\
    \    vector< vector< int > > group(g.size());\n    for(int i = 0; i < (int) g.size();\
    \ i++) group[uf.find(i)].emplace_back(i);\n    vector< vector< int > > ret;\n\
    \    used_edge.assign(M, 0);\n    for(auto &vs : group) {\n      if(vs.empty())\
    \ continue;\n      int latte = -1, malta = -1;\n      if(directed) {\n       \
    \ for(auto &p : vs) {\n          if(abs(deg[p]) > 1) {\n            return {};\n\
    \          } else if(deg[p] == 1) {\n            if(latte >= 0) return {};\n \
    \           latte = p;\n          }\n        }\n      } else {\n        for(auto\
    \ &p : vs) {\n          if(deg[p] & 1) {\n            if(latte == -1) latte =\
    \ p;\n            else if(malta == -1) malta = p;\n            else return {};\n\
    \          }\n        }\n      }\n      ret.emplace_back(go(latte == -1 ? vs.front()\
    \ : latte));\n      if(ret.back().empty()) ret.pop_back();\n    }\n    return\
    \ ret;\n  }\n\n  vector< int > go(int s) {\n    stack< pair< int, int > > st;\n\
    \    vector< int > ord;\n    st.emplace(s, -1);\n    while(!st.empty()) {\n  \
    \    int idx = st.top().first;\n      used_vertex[idx] = true;\n      if(g[idx].empty())\
    \ {\n        ord.emplace_back(st.top().second);\n        st.pop();\n      } else\
    \ {\n        auto e = g[idx].back();\n        g[idx].pop_back();\n        if(used_edge[e.second])\
    \ continue;\n        used_edge[e.second] = true;\n        st.emplace(e);\n   \
    \   }\n    }\n    ord.pop_back();\n    reverse(ord.begin(), ord.end());\n    return\
    \ ord;\n  }\n};\n#line 6 \"graph/others/bipartite-graph-edge-coloring.hpp\"\n\n\
    /**\n * @brief Bipartite Graph Edge Coloring(\u4E8C\u90E8\u30B0\u30E9\u30D5\u306E\
    \u8FBA\u5F69\u8272)\n * @docs docs/bipartite-graph-edge-coloring.md\n * @see https://ei1333.hateblo.jp/entry/2020/08/25/015955\n\
    \ */\nstruct BipariteGraphEdgeColoring {\nprivate:\n  vector< vector< int > >\
    \ ans;\n  vector< int > A, B;\n  int L, R;\n\n  struct RegularGraph {\n    int\
    \ k{}, n{};\n    vector< int > A, B;\n  };\n  RegularGraph g;\n\n  static UnionFind\
    \ contract(valarray< int > &deg, int k) {\n    using pi = pair< int, int >;\n\
    \    priority_queue< pi, vector< pi >, greater<> > que;\n    for(int i = 0; i\
    \ < (int) deg.size(); i++) {\n      que.emplace(deg[i], i);\n    }\n    UnionFind\
    \ uf(deg.size());\n    while(que.size() > 1) {\n      auto p = que.top();\n  \
    \    que.pop();\n      auto q = que.top();\n      que.pop();\n      if(p.first\
    \ + q.first > k) continue;\n      p.first += q.first;\n      uf.unite(p.second,\
    \ q.second);\n      que.emplace(p);\n    }\n    return uf;\n  }\n\n\n  RegularGraph\
    \ build_k_regular_graph() {\n    valarray< int > deg[2];\n    deg[0] = valarray<\
    \ int >(L);\n    deg[1] = valarray< int >(R);\n    for(auto &p : A) deg[0][p]++;\n\
    \    for(auto &p : B) deg[1][p]++;\n\n    int k = max(deg[0].max(), deg[1].max());\n\
    \n    /* step 1 */\n    UnionFind uf[2];\n    uf[0] = contract(deg[0], k);\n \
    \   uf[1] = contract(deg[1], k);\n\n    vector< int > id[2];\n    int ptr[] =\
    \ {0, 0};\n    id[0] = vector< int >(L);\n    id[1] = vector< int >(R);\n    for(int\
    \ i = 0; i < L; i++) if(uf[0].find(i) == i) id[0][i] = ptr[0]++;\n    for(int\
    \ i = 0; i < R; i++) if(uf[1].find(i) == i) id[1][i] = ptr[1]++;\n\n    /* step\
    \ 2 */\n    int N = max(ptr[0], ptr[1]);\n    deg[0] = valarray< int >(N);\n \
    \   deg[1] = valarray< int >(N);\n\n    /* step 3 */\n    vector< int > C, D;\n\
    \    C.reserve(N * k);\n    D.reserve(N * k);\n    for(int i = 0; i < (int) A.size();\
    \ i++) {\n      int u = id[0][uf[0].find(A[i])];\n      int v = id[1][uf[1].find(B[i])];\n\
    \      C.emplace_back(u);\n      D.emplace_back(v);\n      deg[0][u]++;\n    \
    \  deg[1][v]++;\n    }\n    int j = 0;\n    for(int i = 0; i < N; i++) {\n   \
    \   while(deg[0][i] < k) {\n        while(deg[1][j] == k) ++j;\n        C.emplace_back(i);\n\
    \        D.emplace_back(j);\n        ++deg[0][i];\n        ++deg[1][j];\n    \
    \  }\n    }\n\n    return {k, N, C, D};\n  }\n\n  void rec(const vector< int >\
    \ &ord, int k) {\n    if(k == 0) {\n      return;\n    } else if(k == 1) {\n \
    \     ans.emplace_back(ord);\n      return;\n    } else if((k & 1) == 0) {\n \
    \     EulerianTrail< false > et(g.n + g.n);\n      for(auto &p : ord) et.add_edge(g.A[p],\
    \ g.B[p] + g.n);\n      auto paths = et.enumerate_eulerian_trail();\n      vector<\
    \ int > path;\n      for(auto &ps : paths) {\n        for(auto &e : ps) path.emplace_back(ord[e]);\n\
    \      }\n      vector< int > beet[2];\n      for(int i = 0; i < (int) path.size();\
    \ i++) {\n        beet[i & 1].emplace_back(path[i]);\n      }\n      rec(beet[0],\
    \ k / 2);\n      rec(beet[1], k / 2);\n    } else {\n      BipartiteFlow flow(g.n,\
    \ g.n);\n      for(auto &i : ord) flow.add_edge(g.A[i], g.B[i]);\n      flow.max_matching();\n\
    \      vector< int > beet;\n      ans.emplace_back();\n      for(auto &i : ord)\
    \ {\n        if(flow.match_l[g.A[i]] == g.B[i]) {\n          flow.match_l[g.A[i]]\
    \ = -1;\n          ans.back().emplace_back(i);\n        } else {\n          beet.emplace_back(i);\n\
    \        }\n      }\n      rec(beet, k - 1);\n    }\n  }\n\npublic:\n  explicit\
    \ BipariteGraphEdgeColoring() : L(0), R(0) {}\n\n  void add_edge(int a, int b)\
    \ {\n    A.emplace_back(a);\n    B.emplace_back(b);\n    L = max(L, a + 1);\n\
    \    R = max(R, b + 1);\n  }\n\n  vector< vector< int > > build() {\n    g = build_k_regular_graph();\n\
    \    vector< int > ord(g.A.size());\n    iota(ord.begin(), ord.end(), 0);\n  \
    \  rec(ord, g.k);\n    vector< vector< int > > res;\n    for(int i = 0; i < (int)\
    \ ans.size(); i++) {\n      res.emplace_back();\n      for(auto &j : ans[i]) if(j\
    \ < (int)A.size()) res.back().emplace_back(j);\n    }\n    return res;\n  }\n\
    };\n"
  code: "#pragma once\n\n#include \"../../structure/union-find/union-find.hpp\"\n\
    #include \"../flow/bipartite-flow.hpp\"\n#include \"eulerian-trail.hpp\"\n\n/**\n\
    \ * @brief Bipartite Graph Edge Coloring(\u4E8C\u90E8\u30B0\u30E9\u30D5\u306E\u8FBA\
    \u5F69\u8272)\n * @docs docs/bipartite-graph-edge-coloring.md\n * @see https://ei1333.hateblo.jp/entry/2020/08/25/015955\n\
    \ */\nstruct BipariteGraphEdgeColoring {\nprivate:\n  vector< vector< int > >\
    \ ans;\n  vector< int > A, B;\n  int L, R;\n\n  struct RegularGraph {\n    int\
    \ k{}, n{};\n    vector< int > A, B;\n  };\n  RegularGraph g;\n\n  static UnionFind\
    \ contract(valarray< int > &deg, int k) {\n    using pi = pair< int, int >;\n\
    \    priority_queue< pi, vector< pi >, greater<> > que;\n    for(int i = 0; i\
    \ < (int) deg.size(); i++) {\n      que.emplace(deg[i], i);\n    }\n    UnionFind\
    \ uf(deg.size());\n    while(que.size() > 1) {\n      auto p = que.top();\n  \
    \    que.pop();\n      auto q = que.top();\n      que.pop();\n      if(p.first\
    \ + q.first > k) continue;\n      p.first += q.first;\n      uf.unite(p.second,\
    \ q.second);\n      que.emplace(p);\n    }\n    return uf;\n  }\n\n\n  RegularGraph\
    \ build_k_regular_graph() {\n    valarray< int > deg[2];\n    deg[0] = valarray<\
    \ int >(L);\n    deg[1] = valarray< int >(R);\n    for(auto &p : A) deg[0][p]++;\n\
    \    for(auto &p : B) deg[1][p]++;\n\n    int k = max(deg[0].max(), deg[1].max());\n\
    \n    /* step 1 */\n    UnionFind uf[2];\n    uf[0] = contract(deg[0], k);\n \
    \   uf[1] = contract(deg[1], k);\n\n    vector< int > id[2];\n    int ptr[] =\
    \ {0, 0};\n    id[0] = vector< int >(L);\n    id[1] = vector< int >(R);\n    for(int\
    \ i = 0; i < L; i++) if(uf[0].find(i) == i) id[0][i] = ptr[0]++;\n    for(int\
    \ i = 0; i < R; i++) if(uf[1].find(i) == i) id[1][i] = ptr[1]++;\n\n    /* step\
    \ 2 */\n    int N = max(ptr[0], ptr[1]);\n    deg[0] = valarray< int >(N);\n \
    \   deg[1] = valarray< int >(N);\n\n    /* step 3 */\n    vector< int > C, D;\n\
    \    C.reserve(N * k);\n    D.reserve(N * k);\n    for(int i = 0; i < (int) A.size();\
    \ i++) {\n      int u = id[0][uf[0].find(A[i])];\n      int v = id[1][uf[1].find(B[i])];\n\
    \      C.emplace_back(u);\n      D.emplace_back(v);\n      deg[0][u]++;\n    \
    \  deg[1][v]++;\n    }\n    int j = 0;\n    for(int i = 0; i < N; i++) {\n   \
    \   while(deg[0][i] < k) {\n        while(deg[1][j] == k) ++j;\n        C.emplace_back(i);\n\
    \        D.emplace_back(j);\n        ++deg[0][i];\n        ++deg[1][j];\n    \
    \  }\n    }\n\n    return {k, N, C, D};\n  }\n\n  void rec(const vector< int >\
    \ &ord, int k) {\n    if(k == 0) {\n      return;\n    } else if(k == 1) {\n \
    \     ans.emplace_back(ord);\n      return;\n    } else if((k & 1) == 0) {\n \
    \     EulerianTrail< false > et(g.n + g.n);\n      for(auto &p : ord) et.add_edge(g.A[p],\
    \ g.B[p] + g.n);\n      auto paths = et.enumerate_eulerian_trail();\n      vector<\
    \ int > path;\n      for(auto &ps : paths) {\n        for(auto &e : ps) path.emplace_back(ord[e]);\n\
    \      }\n      vector< int > beet[2];\n      for(int i = 0; i < (int) path.size();\
    \ i++) {\n        beet[i & 1].emplace_back(path[i]);\n      }\n      rec(beet[0],\
    \ k / 2);\n      rec(beet[1], k / 2);\n    } else {\n      BipartiteFlow flow(g.n,\
    \ g.n);\n      for(auto &i : ord) flow.add_edge(g.A[i], g.B[i]);\n      flow.max_matching();\n\
    \      vector< int > beet;\n      ans.emplace_back();\n      for(auto &i : ord)\
    \ {\n        if(flow.match_l[g.A[i]] == g.B[i]) {\n          flow.match_l[g.A[i]]\
    \ = -1;\n          ans.back().emplace_back(i);\n        } else {\n          beet.emplace_back(i);\n\
    \        }\n      }\n      rec(beet, k - 1);\n    }\n  }\n\npublic:\n  explicit\
    \ BipariteGraphEdgeColoring() : L(0), R(0) {}\n\n  void add_edge(int a, int b)\
    \ {\n    A.emplace_back(a);\n    B.emplace_back(b);\n    L = max(L, a + 1);\n\
    \    R = max(R, b + 1);\n  }\n\n  vector< vector< int > > build() {\n    g = build_k_regular_graph();\n\
    \    vector< int > ord(g.A.size());\n    iota(ord.begin(), ord.end(), 0);\n  \
    \  rec(ord, g.k);\n    vector< vector< int > > res;\n    for(int i = 0; i < (int)\
    \ ans.size(); i++) {\n      res.emplace_back();\n      for(auto &j : ans[i]) if(j\
    \ < (int)A.size()) res.back().emplace_back(j);\n    }\n    return res;\n  }\n\
    };\n"
  dependsOn:
  - structure/union-find/union-find.hpp
  - graph/flow/bipartite-flow.hpp
  - graph/others/eulerian-trail.hpp
  isVerificationFile: false
  path: graph/others/bipartite-graph-edge-coloring.hpp
  requiredBy: []
  timestamp: '2022-10-23 21:54:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/verify/yosupo-bipartite-edge-coloring.test.cpp
documentation_of: graph/others/bipartite-graph-edge-coloring.hpp
layout: document
redirect_from:
- /library/graph/others/bipartite-graph-edge-coloring.hpp
- /library/graph/others/bipartite-graph-edge-coloring.hpp.html
title: "Bipartite Graph Edge Coloring(\u4E8C\u90E8\u30B0\u30E9\u30D5\u306E\u8FBA\u5F69\
  \u8272)"
---
## 概要

二部グラフの辺彩色を求めるアルゴリズム. 辺彩色とは, 与えられたグラフの辺に色を付けることを指す. このとき隣接する(頂点を共有する)辺は全て異なる色になるようにする.

一般グラフの辺彩色数は, そのグラフの最大次数 $D$ または $D+1$ に一致する. 特に, 二部グラフに限定すると, その辺彩色数は 最大次数 $D$ に一致する.

まず, 与えられたグラフに対して最大次数 $D$ を維持したまま辺を追加したり縮約したりすることで$D-$正則グラフにする. $D$ が偶数の場合, オイラー閉路を求めて, 偶数番目に通った辺, 奇数番目に通った辺に分けて, 再帰的に解く. $D$ が奇数の場合, 完全マッチングを求めてそれらの辺を同じ色で塗った上で消して, 再帰的に解く. これらを繰り返すことで実際に $D$ 色の辺彩色を構成できる.

## 使い方

* `add_edge(a, b)`: $a$ から $b$ に辺を張る. $a$ は二部グラフの左側, $b$ は右側の頂点を指す.
* `build()`: 二部グラフの辺彩色を返す. 同じ色に塗るべき辺の番号が同じ配列に格納される. 辺の番号は `add_edge()` を呼び出した順に 0-indexed で付与される.

## 計算量

$O(M \sqrt N \log D)$

$N$: 頂点数, $M$: 辺の本数, $D$: 頂点の最大次数
