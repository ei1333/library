// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/static_range_count_distinct

#include "../../template/template.hpp"

#include "../../other/static-range-count-distinct.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  vector< int > A(N);
  for(auto& a : A) cin >> a;
  StaticRangeCountDistinct s(A);
  for(int i = 0; i < Q; i++) {
    int l, r;
    cin >> l >> r;
    s.add_query(l, r);
  }
  cout << s.calclate_queries() << "\n";
}
