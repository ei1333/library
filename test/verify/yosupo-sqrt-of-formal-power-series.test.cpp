#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_of_formal_power_series"

#include "../../template/template.cpp"

#include "../../math/combinatorics/mod-int.cpp"
#include "../../math/fft/number-theoretic-transform-friendly-mod-int.cpp"

#include "../../math/combinatorics/mod-pow.cpp"
#include "../../math/combinatorics/mod-sqrt.cpp"

#include "../../math/fps/sqrt.cpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  NumberTheoreticTransformFriendlyModInt< mint > ntt;
  using FPS = FormalPowerSeries< mint >;
  FPS::set_fft([&](FPS &a) { ntt.ntt(a); }, [&](FPS &a) { ntt.intt(a); });
  FPS::set_sqrt([](mint a) { return mod_sqrt< int64_t >(a.x, MOD); });
  int N;
  cin >> N;
  FPS F(N);
  cin >> F;
  auto ret = F.sqrt();
  if(ret.empty()) cout << -1 << endl;
  else cout << ret << endl;
}
