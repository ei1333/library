// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/tetration_mod

#include "../../template/template.hpp"

#include "../../math/combinatorics/mod-tetration.hpp"

int main() {
  int T;
  cin >> T;
  while(T--) {
    int a, b, m;
    cin >> a >> b >> m;
    cout << mod_tetration< int64_t >(a, b, m) % m << "\n";
  }
}
