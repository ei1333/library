// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/sharp_p_subset_sum

#include "../../template/template.hpp"

#include "../../math/combinatorics/mod-int.hpp"
#include "../../math/fps/formal-power-series-friendly-ntt.hpp"
#include "../../math/fps/count-subset-sum.hpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  int N, T;
  cin >> N >> T;
  vector< mint > c(T + 1);
  for(int i = 0; i < N; i++) {
    int s;
    cin >> s;
    c[s] += 1;
  }
  auto ret = count_subset_sum< FPS >(c);
  ret.erase(begin(ret));
  cout << ret << "\n";
}
