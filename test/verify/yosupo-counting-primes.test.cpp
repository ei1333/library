#define PROBLEM "https://judge.yosupo.jp/problem/counting_primes"

#include "../../math/number-theory/prime-count.hpp"
#include "../../template/template.hpp"

int main() {
  int64_t n;
  cin >> n;
  PrimeCount<> pc;
  cout << pc.pi(n) << "\n";
}
