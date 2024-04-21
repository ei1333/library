// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/bitwise_and_convolution

#include "../../template/template.hpp"

#include "../../math/fft/bitwise-or-convolution.hpp"
#include "../../math/combinatorics/mod-int.hpp"

#include "../../other/scanner.hpp"
#include "../../other/printer.hpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

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
  reverse(begin(a), end(a));
  reverse(begin(b), end(b));
  auto c = bitwise_or_convolution(a, b);
  reverse(begin(c), end(c));
  for(int i = 0; i < (1 << N); i++) {
    if(i) out.write(' ');
    out.write(c[i].x);
  }
  out.writeln();
}
