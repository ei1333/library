// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/bitwise_xor_convolution

#include "../../template/template.hpp"

#include "../../math/fft/bitwise-xor-convolution.hpp"
#include "../../math/combinatorics/montgomery-mod-int.hpp"

#include "../../other/scanner.hpp"
#include "../../other/printer.hpp"

using mint = modint998244353;

int main() {
  Scanner in(stdin);
  Printer out(stdout);
  int N;
  in.read(N);
  vector< mint > a(1 << N), b(1 << N);
  for(auto &x : a) {
    int p;
    in.read(p);
    x = p;
  }
  for(auto &x : b) {
    int p;
    in.read(p);
    x = p;
  }
  auto c = bitwise_xor_convolution(a, b);
  for(int i = 0; i < (1 << N); i++) {
    if(i) out.write(' ');
    out.write(c[i].val());
  }
  out.writeln();
}
