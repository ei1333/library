#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_G"

#include "../../math/combinatorics/bell-number.hpp"
#include "../../math/combinatorics/mod-int.hpp"
#include "../../template/template.hpp"

int main() {
  int N, K;
  cin >> N >> K;
  cout << bell_number< modint >(N, K) << endl;
}
