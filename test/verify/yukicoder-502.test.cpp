#define PROBLEM "https://yukicoder.me/problems/no/502"

#include "../../template/template.cpp"

#include "../../math/combinatorics/mod-int.cpp"
#include "../../math/combinatorics/factorial.cpp"

#include "../../math/fft/arbitrary-mod-convolution.cpp"

const int MOD = (int) (1e9 + 7);
using mint = ModInt< MOD >;

int main() {
  int N;
  cin >> N;
  ArbitraryModConvolution< mint > fft;
  auto f = [&](vector< mint > &a, vector< mint > &b) { return fft.multiply(a, b); };
  cout << factorial< mint >(N, f) << "\n";
}
