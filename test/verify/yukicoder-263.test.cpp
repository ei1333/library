// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/263

#include "../../template/template.hpp"

#include "../../string/palindromic-tree.hpp"

int main() {
  string S, T;
  cin >> S >> T;
  PalindromicTree t(S + "><" + T);
  vector< int > dps(1111111), dpt(1111111);
  for(int i = 0; i < t.size(); i++) {
    for(auto &j: t[i].idx) {
      if(j < (int) S.size()) ++dps[i];
      else if(j >= (int) S.size() + 2) ++dpt[i];
    }
  }
  int64 ret = 0;
  for(int i = t.size() - 1; i > 1; i--) {
    ret += 1LL * dps[i] * dpt[i];
    dps[t[i].suffix_link] += dps[i];
    dpt[t[i].suffix_link] += dpt[i];
  }
  cout << ret << "\n";
}
