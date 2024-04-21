// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3022

#include "../../template/template.hpp"

#include "../../graph/others/block-cut-tree.hpp"

int main() {
  int N, M;
  cin >> N >> M;
  vector< int > A(N);
  cin >> A;
  BlockCutTree<> bct(N);
  bct.read(M);
  bct.build();
  vector< int64 > weight(bct.tree.size());
  int64 all = 0;
  for(int i = 0; i < N; i++) {
    weight[bct[i]] += A[i];
    all += A[i];
  }
  vector< int64 > ans(N, all);
  for(int i = 0; i < N; i++) {
    ans[i] -= A[i];
  }
  MFP([&](auto rec, int idx, int par) -> int64 {
    int64 mx = 0, sum = 0;
    for(auto &to : bct.tree.g[idx]) {
      if(to == par) continue;
      auto res = rec(to, idx);
      sum += res;
      chmax(mx, res);
    }
    if(idx >= (int)bct.bc.size()) {
      ans[bct.group[idx][0]] = max(all - sum - weight[idx], mx);
    }
    return sum + weight[idx];
  })(0, -1);
  for(auto &p : ans) cout << p << "\n";
}
