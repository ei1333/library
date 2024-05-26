// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/enumerate_quotients

#include "../../template/template.hpp"

#include "../../math/number-theory/enumerate-quotients.hpp"

int main() {
  int64 n;
  cin >> n;
  auto quotients = enumerate_quotients(n);
  cout << quotients.size() << endl;
  for (auto&& [q, l, r] : quotients) {
    cout << q << " ";
  }
  cout << endl;
}
