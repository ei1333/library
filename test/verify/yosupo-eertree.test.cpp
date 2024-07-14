// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/eertree

#include "../../template/template.hpp"

#include "../../string/palindromic-tree.hpp"

#include "../../other/scanner.hpp"
#include "../../other/printer.hpp"

int main() {
  Scanner in(stdin);
  Printer out(stdout);
  string S;
  in.read(S);
  PalindromicTree g;
  vector< int > vs;
  vs.reserve(S.size());
  for (auto &c: S) {
    vs.emplace_back(g.add(c) - 1);
  }
  int n = g.size();
  vector< int > p(n), s(n);
  for (int i = 0; i < n; i++) {
    for (auto &e: g[i].link) {
      if (e.second >= 0) p[e.second] = i - 1;
    }
    s[i] = g[i].suffix_link - 1;
  }
  out.writeln(n - 2);
  for (int i = 2; i < n; i++) out.writeln(p[i], s[i]);
  out.writeln(vs);
}
