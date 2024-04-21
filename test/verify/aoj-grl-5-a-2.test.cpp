// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A

#include "../../template/template.hpp"
#include "../../structure/develop/diameter.hpp"

int main() {
  int N;
  cin >> N;
  LCT lct;
  vector< vector< pair< int, int > > > g(N);
  for(int i = 1; i < N; i++) {
    int x, y, z;
    cin >> x >> y >> z;
    g[x].emplace_back(y, z);
    g[y].emplace_back(x, z);
  }
  vector< LCT::NP > vs(N), es(N);
  auto rec = MFP([&](auto rec, int idx, int par) -> void {
    vs[idx] = lct.alloc(0);
    for(auto &e: g[idx]) {
      if(e.first == par) continue;
      rec(e.first, idx);
      es[e.first] = lct.alloc(e.second);
      lct.link(vs[e.first], es[e.first]);
      lct.link(es[e.first], vs[idx]);
    }
  });
  rec(0, -1);
  cout << lct.query(vs[0]).dia_max << "\n";
}
