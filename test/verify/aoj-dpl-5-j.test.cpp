// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_J

#include "../../template/template.hpp"

#include "../../math/combinatorics/mod-int.hpp"

#include "../../math/combinatorics/partition-table.hpp"

int main() {
  int N, K;
  cin >> N >> K;
  cout << partition_table< modint >(N, K)[N][K] << endl;
}
