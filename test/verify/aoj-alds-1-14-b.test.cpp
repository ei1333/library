#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"

#include "../../template/template.cpp"

#include "../../string/rolling-hash.cpp"

int main() {
  string T, P;
  cin >> T;
  cin >> P;
  auto base = RollingHash::generate_base();
  auto rh1 = RollingHash(T, base);
  auto rh2 = RollingHash(P, base);
  for(int i = 0; i + P.size() <= T.size(); i++) {
    if(rh1.query(i, i + P.size()) == rh2.query(0, P.size())) {
      cout << i << endl;
    }
  }
}
