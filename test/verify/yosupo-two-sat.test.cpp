// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/two_sat

#include "../../template/template.hpp"

#include "../../other/scanner.hpp"
#include "../../other/printer.hpp"

#include "../../graph/others/two-satisfiability.hpp"

int main() {
  Scanner input(stdin);
  Printer output(stdout);

  string s;
  int N, M;
  input.read(s, s, N, M);
  TwoSatisfiability two(N);
  for(int i = 0; i < M; i++) {
    int a, b, c;
    input.read(a, b, c);
    if(a < 0) a = two.rev(-a - 1);
    else --a;
    if(b < 0) b = two.rev(-b - 1);
    else --b;
    two.add_or(a, b);
  }
  auto ret = two.solve();
  if(ret.empty()) {
    output.writeln("s UNSATISFIABLE");
  } else {
    output.writeln("s SATISFIABLE");
    output.write("v ");
    for(size_t i = 0; i < ret.size(); i++) {
      if(ret[i]) ret[i] = i + 1;
      else ret[i] = -i - 1;
    }
    output.write(ret);
    output.writeln(" 0");
  }
}
