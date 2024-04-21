// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1615

#include "../../template/template.hpp"

#include "../../graph/flow/dinic.hpp"
#include "../../graph/flow/maxflow-lower-bound.hpp"

int main() {
  int N, M;
  while(cin >> N >> M, N) {
    vector< int > U(M), V(M);
    for(int i = 0; i < M; i++) {
      cin >> U[i] >> V[i];
      --U[i], --V[i];
    }
    auto check = [&](int low, int high) {
      MaxFlowLowerBound< int, Dinic > flow(N + M + 2);
      int S = N + M, T = N + M + 1;
      for(int i = 0; i < M; i++) {
        flow.add_edge(S, i, 1, 1);
        flow.add_edge(i, M + U[i], 0, 1);
        flow.add_edge(i, M + V[i], 0, 1);
      }
      for(int i = 0; i < N; i++) {
        flow.add_edge(M + i, T, low, high);
      }
      return flow.max_flow(S, T) == M;
    };

    int p = 0, q = N;
    int l = 0;
    for(int r = 0; r <= N; r++) {
      while(l <= r && check(l, r)) {
        p = l, q = r;
        ++l;
      }
    }
    cout << p << " " << q << endl;
  }
}
