// competitive-verifier: IGNORE
// competitive-verifier: PROBLEM https://dmoj.ca/problem/ds5

#include "../../template/template.hpp"

#include "../../structure/develop/dynamic-tree-test.hpp"

#include "../../other/scanner.hpp"
#include "../../other/printer.hpp"

int main() {
  Scanner in(stdin);
  Printer out(stdout);

  int N, M;
  in.read(N, M);
  vector< vector< int > > g(N);
  for(int i = 0; i + 1 < N; i++) {
    int x, y;
    in.read(x, y);
    --x, --y;
    g[x].emplace_back(y);
    g[y].emplace_back(x);
  }
  LCT lct;
  vector< LCT::NP > vs(N);
  for(int i = 0; i < N; i++) {
    T x;
    in.read(x);
    vs[i] = lct.alloc(x);
  }
  int R;
  in.read(R);
  --R;
  MFP([&](auto dfs, int idx, int par) -> void {
    for(auto &to: g[idx]) {
      if(to != par) {
        lct.link(vs[to], vs[idx]);
        dfs(to, idx);
      }
    }
  })(R, -1);

  for(int i = 0; i < M; i++) {
    int k;
    in.read(k);
    if(k == 0) {
      int x, y;
      in.read(x, y);
      --x;
      lct.evert(vs[R]);
      lct.set_propagate_subtree(vs[x], {1, y});
    } else if(k == 1) {
      in.read(R);
      --R;
    } else if(k == 2) {
      int x, y;
      T z;
      in.read(x, y, z);
      --x, --y;
      lct.set_propagate_path(vs[x], vs[y], {1, z});
    } else if(k == 3) {
      int x;
      in.read(x);
      --x;
      lct.evert(vs[R]);
      auto ret = lct.query_subtree(vs[x]);
      out.writeln(min(ret.light_min, ret.path_min));
    } else if(k == 4) {
      int x;
      in.read(x);
      --x;
      lct.evert(vs[R]);
      auto ret = lct.query_subtree(vs[x]);
      out.writeln(max(ret.light_max, ret.path_max));
    } else if(k == 5) {
      int x, y;
      in.read(x, y);
      --x;
      lct.evert(vs[R]);
      lct.set_propagate_subtree(vs[x], {2, y});
    } else if(k == 6) {
      int x, y;
      T z;
      in.read(x, y, z);
      --x, --y;
      lct.set_propagate_path(vs[x], vs[y], {2, z});
    } else if(k == 7) {
      int x, y;
      in.read(x, y);
      --x, --y;
      out.writeln(lct.query_path(vs[x], vs[y]).path_min);
    } else if(k == 8) {
      int x, y;
      in.read(x, y);
      --x, --y;
      out.writeln(lct.query_path(vs[x], vs[y]).path_max);
    } else if(k == 9) {
      int x, y;
      in.read(x, y);
      --x, --y;
      lct.evert(vs[R]);
      if(lct.lca(vs[x], vs[y]) == vs[x]) {
        continue;
      }
      lct.cut(vs[x]);
      lct.link(vs[x], vs[y]);
    } else if(k == 10) {
      int x, y;
      in.read(x, y);
      --x, --y;
      out.writeln(lct.query_path(vs[x], vs[y]).path_sum);
    } else {
      int x;
      in.read(x);
      --x;
      lct.evert(vs[R]);
      auto ret = lct.query_subtree(vs[x]);
      out.writeln(ret.path_sum + ret.light_sum);
    }
  }
}
