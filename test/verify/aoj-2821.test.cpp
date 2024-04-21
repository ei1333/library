// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2821

#include "../../template/template.hpp"

#include "../../structure/union-find/union-find.hpp"

#include "../../graph/tree/tree-isomorphism.hpp"

int main() {
  int N, M;
  cin >> N >> M;
  vector< int > U(M), V(M);
  UnionFind uf(N);
  for(int i = 0; i < M; i++) {
    cin >> U[i] >> V[i];
    --U[i], --V[i];
    uf.unite(U[i], V[i]);
  }
  vector< vector< int > > belong_v(N), belong_e(N);
  for(int i = 0; i < N; i++) {
    belong_v[uf.find(i)].emplace_back(i);
  }
  for(int i = 0; i < M; i++) {
    belong_e[uf.find(U[i])].emplace_back(i);
  }

  cin >> N;
  Graph<> t(N);
  t.read(N - 1);

  int ret = 0;
  vector< int > id(belong_v.size());
  for(int i = 0; i < (int) belong_v.size(); i++) {
    if(uf.find(i) == i) {
      Graph<> g(belong_v[i].size());
      int ptr = 0;
      for(auto &p : belong_v[i]) id[p] = ptr++;
      for(auto &j : belong_e[i]) {
        g.add_edge(id[U[j]], id[V[j]]);
      }
      ret += tree_isomorphism(t, g);
    }
  }
  cout << ret << endl;
}
