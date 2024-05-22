// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/convex_layers

#include "../../template/template.hpp"

#include "../../geometry/convex-layers.hpp"

int main() {
  int n;
  cin >> n;
  vector<pair<int, int>> ps(n);
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    ps[i] = {x, y};
  }
  cout << convex_layers< int, int64, int64 >(ps) << "\n";
}
