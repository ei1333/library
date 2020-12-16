#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_G"

#include "../../template/template.cpp"

#include "../../math/combinatorics/mod-int.cpp"

#include "../../math/combinatorics/bell-number.cpp"

int main() {
  int N, K;
  cin >> N >> K;
  cout << bell_number< modint >(N, K) << endl;
}
