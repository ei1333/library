// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/line_add_get_min

#include "../../template/template.hpp"

#include "../../structure/convex-hull-trick/convex-hull-trick-add-monotone.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  using CHT = ConvexHullTrickAddMonotone< int64, true >;
  vector< CHT > cht;
  auto add = [&](int64 a, int64 b) {
    cht.emplace_back();
    cht.back().add(a, b);
    while(cht.size() >= 2 and cht.back().H.size() >= cht[cht.size() - 2].H.size()) {
      auto X = cht.back().H;
      cht.pop_back();
      auto Y = cht.back().H;
      cht.pop_back();
      reverse(begin(X), end(X));
      reverse(begin(Y), end(Y));
      CHT c;
      int k = 0;
      for(auto &p: X) {
        while(k < (int) Y.size() and Y[k] < p) {
          c.add(Y[k].first, Y[k].second);
          ++k;
        }
        c.add(p.first, p.second);
      }
      while(k < (int) Y.size()) {
        c.add(Y[k].first, Y[k].second);
        ++k;
      }
      cht.emplace_back(c);
    }
  };
  for(int i = 0; i < N; i++) {
    int64 a, b;
    cin >> a >> b;
    add(a, b);
  }
  while(Q--) {
    int t;
    cin >> t;
    if(t == 0) {
      int64 a, b;
      cin >> a >> b;
      add(a, b);
    } else {
      int64 x;
      cin >> x;
      int64 ret = infll;
      for(auto &c: cht) {
        chmin(ret, c.query(x));
      }
      cout << ret << "\n";
    }
  }
}
