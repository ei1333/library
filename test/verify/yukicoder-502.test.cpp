// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/502

#include "../../template/template.hpp"

#include "../../math/combinatorics/mod-int.hpp"
#include "../../math/combinatorics/factorial.hpp"

#include "../../math/fft/arbitrary-mod-convolution.hpp"

const int MOD = (int) (1e9 + 7);
using mint = ModInt< MOD >;

int main() {
  int N;
  cin >> N;
  ArbitraryModConvolution< mint > fft;
  auto f = [&](vector< mint > &a, vector< mint > &b) { return fft.multiply(a, b); };
  cout << factorial< mint >(N, f) << "\n";
}
