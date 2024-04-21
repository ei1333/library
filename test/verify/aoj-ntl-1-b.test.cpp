// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_B

#include "../../template/template.hpp"

#include "../../math/combinatorics/mod-pow.hpp"

int main() {
  int64 M, N;
  cin >> M >> N;
  cout << mod_pow(M, N, (int64)(1e9 + 7)) << endl;
}
