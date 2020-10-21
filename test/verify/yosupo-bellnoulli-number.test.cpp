#define PROBLEM "https://judge.yosupo.jp/problem/bernoulli_number"

#include "../../template/template.cpp"

#include "../../math/combinatorics/mod-int.cpp"
#include "../../math/fft/number-theoretic-transform-friendly-mod-int.cpp"

#include "../../math/fps/bellnoulli.cpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  NumberTheoreticTransformFriendlyModInt< mint > ntt;
  using FPS = FormalPowerSeries< mint >;
  FPS::set_fft([&](FPS &a) { ntt.ntt(a); }, [&](FPS &a) { ntt.intt(a); });

  int N;
  cin >> N;
  cout << bellnoulli< mint >(N) << endl;
}

