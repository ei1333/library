// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/sqrt_mod

#include "../../template/template.hpp"

#include "../../math/combinatorics/mod-pow.hpp"
#include "../../math/combinatorics/mod-sqrt.hpp"

int main() {
  int T;
  cin >> T;
  while(T--) {
    int64_t Y, P;
    cin >> Y >> P;
    cout << mod_sqrt(Y, P) << endl;
  }
}
