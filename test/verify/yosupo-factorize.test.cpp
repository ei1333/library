#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include "../../math/number-theory/fast-prime-factorization.hpp"
#include "../../template/template.hpp"

int main() {
  int Q;
  cin >> Q;
  while (Q--) {
    int64 X;
    cin >> X;
    auto ret = FastPrimeFactorization::prime_factor(X);
    sort(begin(ret), end(ret));
    cout << ret.size() << " ";
    cout << ret << "\n";
  }
}
