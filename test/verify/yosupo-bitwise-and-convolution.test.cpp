#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_and_convolution"

#include "../../template/template.cpp"

#include "../../math/fft/bitwise-and-convolution.cpp"
#include "../../math/combinatorics/mod-int.cpp"

#include "../../other/scanner.cpp"
#include "../../other/printer.cpp"

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
  auto c = bitwise_and_convolution(a, b);
  for(int i = 0; i < (1 << N); i++) {
    if(i) out.write(' ');
    out.write(c[i].x);
  }
  out.writeln();
}
