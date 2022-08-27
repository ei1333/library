#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_J"

#include "../../math/combinatorics/mod-int.hpp"
#include "../../math/combinatorics/partition-table.hpp"
#include "../../template/template.hpp"

int main() {
  int N, K;
  cin >> N >> K;
  cout << partition_table< modint >(N, K)[N][K] << endl;
}
