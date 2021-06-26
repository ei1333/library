#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_of_formal_power_series"

#include "../../template/template.cpp"

#include "../../math/combinatorics/mod-int.cpp"
#include "../../math/combinatorics/mod-pow.cpp"
#include "../../math/combinatorics/mod-sqrt.cpp"

#include "../../math/fps/formal-power-series-friendly-ntt.cpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  int N;
  cin >> N;
  FPS< mint > f(N);
  cin >> f;
  auto get_sqrt = [&](mint x) { return mod_sqrt< int64 >(x.x, mint::get_mod()); };
  f = f.sqrt(get_sqrt);
  if(f.empty()) cout << "-1\n";
  else cout << f << "\n";
}
