// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/primality_test

#include "../../template/template.hpp"

#include "../../math/number-theory/fast-prime-factorization.hpp"

int main() {
  int Q;
  cin >> Q;
  while(Q--) {
    int64 N;
    cin >> N;
    cout << (FastPrimeFactorization::is_prime(N) ? "Yes" : "No") << "\n";
  }
}
