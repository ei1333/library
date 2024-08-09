// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_kth_smallest

#include "../../template/template.hpp"

#include "../../structure/segment-tree/persistent-segment-tree.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  vector< int > A(N);
  for(auto& a : A) cin >> a;
  auto xs = A;
  sort(xs.begin(), xs.end());
  xs.erase(unique(xs.begin(), xs.end()), xs.end());

  auto f = [](int64 a, int64 b) { return a + b; };
  auto e = []() { return 0ll; };
  auto monoid = LambdaMonoid(f, e);
  PersistentSegmentTree  segCnt(monoid, N);
  vector< decltype(segCnt)::NP > cntNP(xs.size() + 1);
  cntNP[0] = segCnt.build(vector< int64 >(N, 0ll));

  vector< vector< int > > upd(xs.size());;
  for(int i = 0; i < N; i++) {
    A[i] = lower_bound(xs.begin(), xs.end(), A[i]) - xs.begin();
    upd[A[i]].emplace_back(i);
  }
  for(int i = 0; i < xs.size(); i++) {
    auto cntNow = cntNP[i];
    for(auto& j : upd[i]) {
      cntNow = segCnt.set(cntNow, j, 1);
    }
    cntNP[i + 1] = cntNow;
  }
  while(Q--) {
    int l, r, k;
    cin >> l >> r >> k;
    int ok = -1, ng = (int) xs.size() - 1;
    auto check = [&](int p) {
      return segCnt.prod(cntNP[p + 1], l, r) <= k;
    };
    while(ng - ok > 1) {
      int mid = (ok + ng) / 2;
      if(check(mid)) ok = mid;
      else ng = mid;
    }
    cout << xs[ok + 1] << "\n";
  }
}
