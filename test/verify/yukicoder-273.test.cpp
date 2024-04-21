// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/273

#include "../../template/template.hpp"

#include "../../string/palindromic-tree.hpp"

int main() {
  string S;
  cin >> S;
  int N = (int) S.size();
  vector< int > dp1(N + 3, -inf), dp2(N + 1, -inf);
  PalindromicTree t;
  dp2[0] = 1;
  for(int i = 0; i < N; i++) {
    int id = t.add(S[i]);
    auto ret = t.update_dp([&](int id, int pos) {
                             if(i + 1 - pos == N) dp1[id] = dp2[pos];
                             else dp1[id] = max(dp2[pos], i + 1 - pos);
                           },
                           [&](int id, int par) {
                             if(t[id].len == N) chmax(dp1[id], dp1[par]);
                             else chmax(dp1[id], max(dp1[par], t[id].len));
                           });
    for(auto &p: ret) chmax(dp2[i + 1], dp1[p]);
  }
  cout << dp2[N] << "\n";
}
