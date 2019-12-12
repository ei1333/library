#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"

#include "../../template/template.cpp"

#include "../../math/combinatorics/mod-int.cpp"
#include "../../math/fft/number-theoretic-transform-friendly-mod-int.cpp"

#include "../../math/fps/formal-power-series.cpp"
#include "../../math/fps/multipoint-evaluation.cpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  NumberTheoreticTransformFriendlyModInt< mint > ntt;
  using FPS = FormalPowerSeries< mint >;
  auto mult = [&](const FPS::P &a, const FPS::P &b) {
    auto ret = ntt.multiply(a, b);
    return FPS::P(ret.begin(), ret.end());
  };
  FPS::set_mult(mult);
  FPS::set_fft([&](FPS::P &a) { ntt.ntt(a); }, [&](FPS::P &a) { ntt.intt(a); });

  int N, M;
  cin >> N >> M;
  FPS as(N), xs(M);
  cin >> as >> xs;
  cout << multipoint_evaluation(as, xs) << endl;
}
