#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A"

#include "../../template/template.cpp"

#include "../../structure/develop/array-pool.cpp"

#include "../../structure/develop/link-cut-tree-subtree.cpp"

#include "../../structure/develop/diameter.cpp"

int main() {
  int N;
  cin >> N;
  using LCT = LinkCutTreeSubTree< Diameter< int >, 200000 >;
  LCT lct;
  vector< vector< pair< int, int > > > g(N);
  for(int i = 1; i < N; i++) {
    int x, y, z;
    cin >> x >> y >> z;
    g[x].emplace_back(y, z);
    g[y].emplace_back(x, z);
  }
  vector< LCT::Node * > vs(N), es(N);
  auto rec = MFP([&](auto rec, int idx, int par) -> void {
    vs[idx] = lct.alloc(make_pair(true, 1));
    for(auto &e : g[idx]) {
      if(e.first == par) continue;
      rec(e.first, idx);
      es[e.first] = lct.alloc(make_pair(false, e.second));
      lct.link(vs[e.first], es[e.first]);
      lct.link(es[e.first], vs[idx]);
    }
  });
  rec(0, -1);
  lct.expose(vs[0]);
  cout << vs[0]->sum.diameter << "\n";
}
