// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/subset_convolution

#include "../../template/template.hpp"

#include "../../math/fft/subset-convolution.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"

#include "../../other/scanner.hpp"
#include "../../other/printer.hpp"

const int MOD = 998244353;
using mint = MontgomeryModInt< MOD, true >;

int main() {
  Scanner in(stdin);
  Printer out(stdout);
  int N;
  in.read(N);
  vector< mint > f(1 << N), g(1 << N);
  for(auto &a : f) {
    int x;
    in.read(x);
    a = x;
  }
  for(auto &a : g) {
    int x;
    in.read(x);
    a = x;
  }
  auto h = SubsetConvolution< mint, 20 >::multiply(f, g);
  for(auto &a : h) {
    out.write(a.get());
    out.write(' ');
  }
  out.writeln();
}
