// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B

#include "../../template/template.hpp"

#include "../../string/rolling-hash.hpp"

int main() {
  string T, P;
  cin >> T;
  cin >> P;
  RollingHash roll;
  auto rh1 = roll.build(T);
  auto rh2 = roll.build(P);
  for(int i = 0; i + P.size() <= T.size(); i++) {
    if(roll.query(rh1, i, i + P.size()) == roll.query(rh2, 0, P.size())) {
      cout << i << endl;
    }
  }
}
