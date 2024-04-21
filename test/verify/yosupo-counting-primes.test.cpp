// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/counting_primes

#include "../../template/template.hpp"

#include "../../math/number-theory/prime-count.hpp"

int main() {
  int64_t n;
  cin >> n;
  PrimeCount<> pc;
  cout << pc.pi(n) << "\n";
}
