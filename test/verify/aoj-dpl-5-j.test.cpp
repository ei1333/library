#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_J"

#include "../../template/template.cpp"

#include "../../math/combinatorics/mod-int.cpp"

#include "../../math/combinatorics/partition-table.cpp"

int main() {
  int N, K;
  cin >> N >> K;
  cout << partition_table< modint >(N, K)[N][K] << endl;
}
