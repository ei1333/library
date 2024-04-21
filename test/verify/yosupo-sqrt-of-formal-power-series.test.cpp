// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/sqrt_of_formal_power_series

#include "../../template/template.hpp"

#include "../../math/combinatorics/mod-int.hpp"
#include "../../math/combinatorics/mod-pow.hpp"
#include "../../math/combinatorics/mod-sqrt.hpp"

#include "../../math/fps/formal-power-series-friendly-ntt.hpp"

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
