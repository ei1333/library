// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_A

#include "../../template/template.hpp"

#include "../../graph/mst/boruvka.hpp"

int main() {
  int V, E;
  cin >> V >> E;
  vector< int > X(E), Y(E), Z(E);
  for(int i = 0; i < E; i++) {
    cin >> X[i] >> Y[i] >> Z[i];
  }
  Boruvka< int > mst(V);
  auto f = [&](vector< pair< int, int > > &ret) {
    for(int i = 0; i < E; i++) {
      X[i] = mst.find(X[i]);
      Y[i] = mst.find(Y[i]);
      if(X[i] == Y[i]) continue;
      ret[X[i]] = min(ret[X[i]], make_pair(Z[i], Y[i]));
      ret[Y[i]] = min(ret[Y[i]], make_pair(Z[i], X[i]));
    }
    return ret;
  };
  cout << mst.build(f) << endl;
}
