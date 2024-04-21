// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/suffixarray

#include "../../template/template.hpp"

#include "../../string/suffix-array.hpp"

int main() {
  string s;
  cin >> s;
  auto sa = SuffixArray(s);
  sa.erase(sa.begin());
  cout << sa << "\n";
}
