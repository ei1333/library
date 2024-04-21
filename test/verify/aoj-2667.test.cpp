// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2667

#include "../../template/template.hpp"

#include "../../graph/tree/heavy-light-decomposition.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  HeavyLightDecomposition<> hld(N);
  hld.read(N - 1, 0);
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
      Graph<> h(remark.size());
      for(auto &p : es) {
        p.first = index[p.first];
        p.second = index[p.second];
        par[p.second] = p.first;
        dist[p.second] = hld.dist(remark[p.first], remark[p.second]);
        h.add_directed_edge(p.first, p.second);
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
            for(auto &to : h.g[idx]) {
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
        for(auto &to : hld.g[idx]) {
          if(to != par) dfs(to, idx, add, all);
        }
      })(0, -1, 0, 0);
      qs.clear();
      remark.clear();
    }
  }
}
