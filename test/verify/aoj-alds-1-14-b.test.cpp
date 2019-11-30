#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"

#include "../../template/template.cpp"

#include "../../string/rolling-hash.cpp"

int main() {
  string T, P;

  cin >> T;
  cin >> P;
  RH rh(T), rh2(P);
  for(int i = 0; i + P.size() <= T.size(); i++) {
    if(rh.get(i, i + P.size()) == rh2.get(0, P.size())) {
      cout << i << endl;
    }
  }
}
