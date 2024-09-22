// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B

#include "../../template/template.hpp"

#include "../../string/rolling-hash.hpp"

int main() {
  string T, P;
  cin >> T;
  cin >> P;
  RollingHash rh1(T), rh2(P);
  for(int i = 0; i + P.size() <= T.size(); i++) {
    if(rh1.get(i, i + P.size()) == rh2.get(0, P.size())) {
      cout << i << endl;
    }
  }
}
