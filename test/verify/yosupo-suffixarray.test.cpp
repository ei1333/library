#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "../../string/suffix-array.hpp"
#include "../../template/template.hpp"

int main() {
  string s;
  cin >> s;
  auto sa = SuffixArray(s);
  sa.erase(sa.begin());
  cout << sa << "\n";
}
