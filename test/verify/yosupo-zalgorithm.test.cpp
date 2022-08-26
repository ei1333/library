#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../../string/z-algorithm.hpp"
#include "../../template/template.hpp"

int main() {
  string s;
  cin >> s;
  cout << ZAlgorithm(s).get() << "\n";
}
