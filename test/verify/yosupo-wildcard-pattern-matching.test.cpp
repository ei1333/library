// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/wildcard_pattern_matching

#include "../../template/template.hpp"

#include "../../string/wildcard-pattern-matching.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"

int main() {
  string S, T;
  cin >> S >> T;
  for(auto& a : wildcard_pattern_matching< modint998244353 >(S, T, '*')) {
    cout << a;
  }
  cout << endl;
}
