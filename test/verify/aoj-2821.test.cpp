#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2821"

#include "../../template/template.cpp"
#include "../../graph/template.cpp"

#include "../../structure/union-find/union-find.cpp"

#include "../../graph/tree/centroid.cpp"
#include "../../graph/tree/tree-isomorphism.cpp"

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
  UnWeightedGraph t(N);
  for(int i = 1; i < N; i++) {
    int x, y;
    cin >> x >> y;
    --x, --y;
    t[x].emplace_back(y);
    t[y].emplace_back(x);
  }

  int ret = 0;
  vector< int > id(belong_v.size());
  for(int i = 0; i < (int) belong_v.size(); i++) {
    if(uf.find(i) == i) {
      UnWeightedGraph g(belong_v[i].size());
      int ptr = 0;
      for(auto &p : belong_v[i]) id[p] = ptr++;
      for(auto &j : belong_e[i]) {
        g[id[U[j]]].emplace_back(id[V[j]]);
        g[id[V[j]]].emplace_back(id[U[j]]);
      }
      ret += tree_isomorphism(t, g);
    }
  }
  cout << ret << endl;
}

