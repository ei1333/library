#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"

#include "../../template/template.cpp"

#include "../../math/combinatorics/mod-int.cpp"

#include "../../math/fps/formal-power-series.cpp"

#include "../../math/fps/berlekamp-massey.cpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  int N;
  cin >> N;
  FormalPowerSeries< mint > A(N);
  cin >> A;
  auto C = berlekamp_massey(A);
  const int d = (int) C.size() - 1;
  cout << d << endl;
  for(int j = 1; j <= d; j++) cout << C[d - j] << " ";
  cout << endl;
}
