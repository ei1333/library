#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_J"

#include "../../template/template.cpp"

#include "../mod-int.cpp"

#include "../partition-table.cpp"

int main() {
  int N, K;
  cin >> N >> K;
  cout << get_partition< modint >(N, K)[N][K] << endl;
}
