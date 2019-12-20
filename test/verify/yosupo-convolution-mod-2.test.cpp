#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "../../template/template.cpp"

#include "../../math/combinatorics/mod-int.cpp"

#include "../../math/fft/fast-fourier-transform.cpp"
#include "../../math/fft/arbitrary-mod-convolution.cpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  int N, M;
  cin >> N >> M;
  vector< mint > A(N), B(M);
  for(auto &a : A) cin >> a;
  for(auto &b : B) cin >> b;
  ArbitraryModConvolution< mint > fft;
  for(auto &c : fft.multiply(A, B)) cout << c << " ";
  cout << endl;
}
