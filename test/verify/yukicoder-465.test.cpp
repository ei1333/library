// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/465

#include "../../template/template.hpp"

#include "../../string/palindromic-tree.hpp"

int main() {
  string S;
  cin >> S;
  int N = (int) S.size();
  vector< int64 > dp1(N + 1), dp2(N + 1);
  vector< int64 > buf(N + 3);
  PalindromicTree t;
  for(int i = 0; i < N; i++) {
    int id = t.add(S[i]);
    if(t[id].len == i + 1) dp1[i + 1] = 1;
    auto ret = t.update_dp([&](int id, int pos) {
                             buf[id] = dp1[pos];
                           },
                           [&](int id, int par) {
                             buf[id] += buf[par];
                           });
    for(auto &p: ret) dp2[i + 1] += buf[p];
  }
  PalindromicTree ts;
  int64 ret = 0, sum = 0;
  for(int i = N - 1; i >= 0; i--) {
    ret += 1LL * dp2[i] * sum;
    int id = ts.add(S[i]);
    if(ts[id].len == N - i) {
      sum++;
    }
  }
  cout << ret << "\n";
}
