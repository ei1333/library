#define PROBLEM "https://judge.yosupo.jp/problem/tetration_mod"

#include "../../template/template.cpp"

#include "../../math/combinatorics/mod-tetration.cpp"

int main() {
  int T;
  cin >> T;
  while(T--) {
    int a, b, m;
    cin >> a >> b >> m;
    cout << mod_tetration< int64_t >(a, b, m) % m << "\n";
  }
}
