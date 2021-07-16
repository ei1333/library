#define PROBLEM "https://judge.yosupo.jp/problem/counting_primes"

#include "../../template/template.cpp"

#include "../../math/number-theory/prime-count.cpp"

int main() {
  int64_t n;
  cin >> n;
  PrimeCount<> pc;
  cout << pc.pi(n) << "\n";
}
