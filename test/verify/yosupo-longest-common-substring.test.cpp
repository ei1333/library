// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/longest_common_substring

#include "../../template/template.hpp"

#include "../../string/longest-common-substring.hpp"

int main() {
  string S, T;
  cin >> S >> T;
  auto [a, b, c, d] = longest_common_substring(S, T);
  cout << a << " " << b << " " << c << " " << d << endl;
}
