#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"

#include "../../template/template.cpp"

#include "../../math/combinatorics/mod-pow.cpp"
#include "../../math/combinatorics/mod-sqrt.cpp"

int main() {
  int T;
  cin >> T;
  while(T--) {
    int64_t Y, P;
    cin >> Y >> P;
    cout << mod_sqrt(Y, P) << endl;
  }
}
