#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_B"

#include "../../template/template.cpp"

#include "../power.cpp"

int main() {
  int M, N;
  cin >> M >> N;
  cout << power(M, N, 1e9 + 7) << endl;
}
