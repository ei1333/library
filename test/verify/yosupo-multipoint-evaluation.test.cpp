// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/multipoint_evaluation

#include "../../template/template.hpp"

#include "../../math/combinatorics/mod-int.hpp"
#include "../../math/fps/formal-power-series-friendly-ntt.hpp"
#include "../../math/fps/multipoint-evaluation.hpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  int N, M;
  cin >> N >> M;
  FPS< mint > f(N), xs(M);
  cin >> f >> xs;
  cout << multipoint_evaluation(f, xs) << endl;
}
