// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_G

#include "../../template/template.hpp"

#include "../../dp/knapsack-limitations.hpp"

int main() {
  int N, W;
  cin >> N >> W;
  vector< int > v(N), w(N), m(N);
  for(int i = 0; i < N; i++) {
    cin >> v[i] >> w[i] >> m[i];
  }
  auto ret = knapsack_limitations(w, m, v, W, -1);
  cout << *max_element(begin(ret), end(ret)) << endl;
}
