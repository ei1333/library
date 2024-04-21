// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_F

#include "../../template/template.hpp"

#include "../../dp/knapsack-01-2.hpp"

int main() {
  int N, W;
  cin >> N >> W;
  vector< int > v(N), w(N);
  for(int i = 0; i < N; i++) cin >> v[i] >> w[i];
  cout << knapsack_01_2(w, v, W) << endl;
}
