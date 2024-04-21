// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0275

#include "../../template/template.hpp"
#include "../../graph/shortest-path/dijkstra.hpp"
#include "../../graph/others/offline-dag-reachability.hpp"

int main() {
  int S, R, A, B, Q;
  cin >> S >> R;
  Graph< int > g(S);
  vector< int > U(R), V(R), C(R);
  for(int i = 0; i < R; i++) {
    cin >> U[i] >> V[i] >> C[i];
    --U[i], --V[i];
    g.add_edge(U[i], V[i], C[i]);
  }
  cin >> A >> B >> Q;
  --A, --B;
  auto pre = dijkstra(g, A).dist;
  auto suf = dijkstra(g, B).dist;

  Graph< int > dag(S);
  for(int i = 0; i < R; i++) {
    if(pre[U[i]] + C[i] + suf[V[i]] == pre[B]) dag.add_directed_edge(U[i], V[i]);
    if(pre[V[i]] + C[i] + suf[U[i]] == pre[B]) dag.add_directed_edge(V[i], U[i]);
  }
  vector< pair< int, int > > qs(Q);
  for(auto &p : qs) {
    cin >> p.first >> p.second;
    --p.first, --p.second;
  }
  auto ans = offline_dag_reachability(dag, qs);
  for(auto &p : ans) cout << (p ? "Yes\n" : "No\n");
}
