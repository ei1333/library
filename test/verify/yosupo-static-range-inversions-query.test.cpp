// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/static_range_inversions_query

#include "../../template/template.hpp"

#include "../../other/mo.hpp"
#include "../../structure/others/binary-indexed-tree.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  vector< int > A(N);
  for(auto &a : A) cin >> a;
  Mo mo(N);
  for(int i = 0; i < Q; i++) {
    int l, r;
    cin >> l >> r;
    mo.add(l, r);
  }
  vector< int > xs{A};
  sort(begin(xs), end(xs));
  xs.erase(unique(begin(xs), end(xs)), end(xs));
  for(auto &a : A) a = lower_bound(begin(xs), end(xs), a) - begin(xs);
  BinaryIndexedTree< int > bit(xs.size());
  int64_t inv = 0, all = 0;
  vector< int64_t > ans(Q);
  auto add_left = [&](int idx) {
    inv += bit.prod(A[idx]);
    bit.apply(A[idx], 1);
    all++;
  };
  auto add_right = [&](int idx) {
    inv += all - bit.prod(A[idx] + 1);
    bit.apply(A[idx], 1);
    ++all;
  };
  auto erase_left = [&](int idx) {
    inv -= bit.prod(A[idx]);
    bit.apply(A[idx], -1);
    --all;
  };
  auto erase_right = [&](int idx) {
    inv -= all - bit.prod(A[idx] + 1);
    bit.apply(A[idx], -1);
    --all;
  };
  auto out = [&](int idx) {
    ans[idx] = inv;
  };
  mo.build(add_left, add_right, erase_left, erase_right, out);
  for(auto &p : ans) cout << p << "\n";
}
