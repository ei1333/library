// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/directedmst

#include "../../template/template.hpp"

#include "../../graph/mst/directed-mst.hpp"

int main() {
  int n, m, r;
  cin >> n >> m >> r;
  Edges< int64_t > edges;
  for(int i = 0; i < m; ++i) {
    int a, b;
    int64_t w;
    cin >> a >> b >> w;
    edges.emplace_back(a, b, w);
  }
  auto res = directed_mst(n, r, edges);
  cout << res.cost << "\n";
  vector< int > ans(n);
  ans[r] = r;
  for(auto &e : res.edges) {
    ans[e.to] = e.from;
  }
  cout << ans << "\n";
}
