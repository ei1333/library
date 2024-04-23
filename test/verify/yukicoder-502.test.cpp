// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/502

#include "../../template/template.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/combinatorics/factorial.hpp"

#include "../../math/fft/arbitrary-mod-convolution.hpp"

using mint = modint1000000007;

int main() {
  int N;
  cin >> N;
  ArbitraryModConvolution< mint > fft;
  auto f = [&](vector< mint > &a, vector< mint > &b) { return fft.multiply(a, b); };
  cout << factorial< mint >(N, f) << "\n";
}
