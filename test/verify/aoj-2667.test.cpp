#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2667"

#include "../../template/template.cpp"
#include "../../graph/template.cpp"

#include "../../graph/tree/heavy-light-decomposition.cpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  UnWeightedGraph g(N);
  for(int i = 1; i < N; i++) {
    int a, b;
    cin >> a >> b;
    g[a].emplace_back(b);
    g[b].emplace_back(a);
  }
  HeavyLightDecomposition< UnWeightedGraph > hld(g);
  hld.build();

  struct Query {
    int t, a, b;

    void input() {
      cin >> t >> a >> b;
    }
  };

  vector< int > remark;
  vector< Query > qs;
  vector< int64 > sum(N);

  vector< int > index(N);
  for(int i = 0; i < Q; i++) {
    Query q;
    q.input();
    qs.emplace_back(q);
    if(q.t == 0) {
      remark.emplace_back(q.a);
      remark.emplace_back(q.b);
    } else {
      remark.emplace_back(q.a);
    }
    if(remark.size() >= 2000 || i + 1 == Q) {
      auto es = hld.compress(remark);
      for(int j = 0; j < remark.size(); j++) index[remark[j]] = j;
      vector< int > dist(remark.size()), par(remark.size());
      UnWeightedGraph h(remark.size());
      for(auto &p : es) {
        p.first = index[p.first];
        p.second = index[p.second];
        par[p.second] = p.first;
        dist[p.second] = hld.dist(remark[p.first], remark[p.second]);
        h[p.first].emplace_back(p.second);
      }
      vector< int64 > lazy_add(N), backet_add(N);
      for(auto &q : qs) {
        if(q.t == 0) {
          int64 ret = 0;
          ret += sum[q.a] + sum[q.b] - 2 * sum[hld.lca(q.a, q.b)];
          ret += backet_add[q.a] + backet_add[q.b] - 2 * backet_add[hld.lca(q.a, q.b)];
          cout << ret << "\n";
        } else {
          lazy_add[q.a] += q.b;
          q.a = index[q.a];
          MFP([&](auto dfs, int idx, int p, int64 sz) -> void {
            for(auto &to : h[idx]) {
              if(to != p) {
                backet_add[remark[to]] += (sz + dist[to]) * q.b;
                dfs(to, idx, sz + dist[to]);
              }
            }
          })(q.a, par[q.a], 0);
        }
      }
      MFP([&](auto dfs, int idx, int par, int64 add, int64 all) -> void {
        all += add;
        add += lazy_add[idx];
        sum[idx] += all;
        for(auto &to : g[idx]) {
          if(to != par) dfs(to, idx, add, all);
        }
      })(0, -1, 0, 0);
      qs.clear();
      remark.clear();
    }
  }
}

