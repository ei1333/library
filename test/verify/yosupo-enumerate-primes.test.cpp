// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/enumerate_primes

#include "../../template/template.hpp"

#include "../../math/number-theory/enumerate-primes.hpp"

int main() {
  int N, A, B;
  cin >> N >> A >> B;
  auto d = enumerate_primes(N);
  vector< int > ans;
  for(int i = B; i < d.size(); i += A) {
    ans.emplace_back(d[i]);
  }
  cout << d.size() << " " << ans.size() << "\n";
  cout << ans << "\n";
}
