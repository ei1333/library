// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/persistent_unionfind

#include "../../template/template.hpp"

#include "../../structure/others/persistent-array.hpp"
#include "../../structure/union-find/persistent-union-find.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  vector< PersistentUnionFind > uf(Q + 1);
  uf[0] = PersistentUnionFind(N);
  for(int i = 1; i <= Q; i++) {
    int t, k, u, v;
    cin >> t >> k >> u >> v;
    ++k;
    if(t == 0) {
      uf[i] = uf[k];
      uf[i].unite(u, v);
    } else {
      cout << (uf[k].find(u) == uf[k].find(v)) << "\n";
    }
  }
}
