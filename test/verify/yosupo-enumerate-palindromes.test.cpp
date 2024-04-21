// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/enumerate_palindromes

#include "../../template/template.hpp"

#include "../../string/manacher.hpp"

int main() {
  string s;
  cin >> s;
  cout << manacher(s) << "\n";
}
