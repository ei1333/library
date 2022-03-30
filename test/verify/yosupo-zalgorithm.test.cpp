#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include "../../template/template.cpp"

#include "../../string/z-algorithm.hpp"

int main() {
  string s;
  cin >> s;
  cout << ZAlgorithm(s).get() << "\n";
}
