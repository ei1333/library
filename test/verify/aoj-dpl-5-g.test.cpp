// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_G

#include "../../template/template.hpp"

#include "../../math/combinatorics/mod-int.hpp"

#include "../../math/combinatorics/bell-number.hpp"

int main() {
  int N, K;
  cin >> N >> K;
  cout << bell_number< modint >(N, K) << endl;
}
