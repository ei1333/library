#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../template/template.cpp"

#include "../../math/combinatorics/montgomery-mod-int.cpp"
#include "../../math/fft/number-theoretic-transform-friendly-mod-int.cpp"

const int MOD = 998244353;
using mint = MontgomeryModInt< MOD, true >;

int main() {
  int N, M;
  cin >> N >> M;
  vector< mint > A(N), B(M);
  for(auto &a : A) cin >> a;
  for(auto &b : B) cin >> b;
  NumberTheoreticTransformFriendlyModInt< mint > ntt;
  for(auto &c : ntt.multiply(A, B)) cout << c << " ";
  cout << endl;
}
