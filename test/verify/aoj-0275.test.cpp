#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0275"

#include "../../template/template.cpp"
#include "../../graph/template.cpp"

#include "../../graph/shortest-path/dijkstra.cpp"

#include "../../graph/others/topological-sort.cpp"

#include "../../graph/others/offline-dag-reachability.cpp"

int main() {
  int S, R, A, B, Q;
  cin >> S >> R;
  WeightedGraph< int > g(S);
  vector< int > U(R), V(R), C(R);
  for(int i = 0; i < R; i++) {
    cin >> U[i] >> V[i] >> C[i];
    --U[i], --V[i];
    g[U[i]].emplace_back(V[i], C[i]);
    g[V[i]].emplace_back(U[i], C[i]);
  }
  cin >> A >> B >> Q;
  --A, --B;
  auto pre = dijkstra(g, A);
  auto suf = dijkstra(g, B);

  UnWeightedGraph dag(S);
  for(int i = 0; i < R; i++) {
    if(pre[U[i]] + C[i] + suf[V[i]] == pre[B]) dag[U[i]].emplace_back(V[i]);
    if(pre[V[i]] + C[i] + suf[U[i]] == pre[B]) dag[V[i]].emplace_back(U[i]);
  }
  vector< pair< int, int > > qs(Q);
  for(auto &p : qs) {
    cin >> p.first >> p.second;
    --p.first, --p.second;
  }
  auto ans = offline_dag_reachability(dag, qs);
  for(auto &p : ans) cout << (p ? "Yes\n" : "No\n");
}
