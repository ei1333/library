#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

#include "../../dp/cumulative-sum.hpp"
#include "../../template/template.hpp"

int main() {
  int n, q;
  cin >> n >> q;
  CumulativeSum< int64 > cs(n);
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    cs.add(i, x);
  }
  cs.build();
  for (int i = 0; i < q; i++) {
    int l, r;
    cin >> l >> r;
    cout << cs.fold(l, r) << "\n";
  }
}
