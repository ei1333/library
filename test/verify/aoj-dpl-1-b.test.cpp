// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_B

#include "../../template/template.hpp"

#include "../../dp/knapsack-01.hpp"

int main() {
  int N, W;
  cin >> N >> W;
  vector< int > v(N), w(N);
  for(int i = 0; i < N; i++) cin >> v[i] >> w[i];
  auto ret = knapsack_01(w, v, W, -1);
  cout << *max_element(begin(ret), end(ret)) << endl;
}
