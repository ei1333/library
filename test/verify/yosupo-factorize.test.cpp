// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/factorize

#include "../../template/template.hpp"

#include "../../math/number-theory/fast-prime-factorization.hpp"

int main() {
  int Q;
  cin >> Q;
  while(Q--) {
    int64 X;
    cin >> X;
    auto ret = FastPrimeFactorization::prime_factor(X);
    sort(begin(ret), end(ret));
    cout << ret.size() << " ";
    cout << ret << "\n";
  }
}
