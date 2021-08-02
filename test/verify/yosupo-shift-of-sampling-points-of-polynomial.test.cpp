#define PROBLEM "https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial"

#include "../../template/template.cpp"

#include "../../math/fft/number-theoretic-transform-friendly-mod-int.cpp"

#include "../../math/combinatorics/lagrange-polynomial-3.cpp"

#include "../../math/combinatorics/mod-int.cpp"

using mint = ModInt< 998244353 >;

int main() {
  int N, T, M;
  cin >> N >> T >> M;
  vector< mint > ys(N);
  for(int i = 0; i < N; i++) cin >> ys[i];
  NumberTheoreticTransformFriendlyModInt< mint > v;
  auto multiply = [&](const vector< mint > &a, const vector< mint > &b) { return v.multiply(a, b); };
  cout << lagrange_polynomial(ys, M, T, multiply) << "\n";
}
