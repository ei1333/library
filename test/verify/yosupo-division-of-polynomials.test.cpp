// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/division_of_polynomials

#include "../../template/template.hpp"

#include "../../math/combinatorics/mod-int.hpp"
#include "../../math/fps/formal-power-series-friendly-ntt.hpp"

#include "../../other/scanner.hpp"
#include "../../other/printer.hpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  Scanner in(stdin);
  Printer out(stdout);

  int N, M;
  in.read(N, M);
  FPS< mint > f, g;
  f.reserve(N);
  g.reserve(M);
  for(int i = 0; i < N; i++) {
    int x;
    in.read(x);
    f.emplace_back(x);
  }
  for(int i = 0; i < M; i++) {
    int x;
    in.read(x);
    g.emplace_back(x);
  }
  auto[q, r] = f.div_mod(g);
  out.writeln(q.size(), r.size());
  for(int i = 0; i < q.size(); i++) {
    if(i > 0) out.write(' ');
    out.write(q[i].x);
  }
  out.writeln();
  for(int i = 0; i < r.size(); i++) {
    if(i > 0) out.write(' ');
    out.write(r[i].x);
  }
  out.writeln();
}

