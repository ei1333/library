#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_A"

#include "../../template/template.cpp"

#include "../../math/number-theory/prime-factor.cpp"

int main() {
  int N;
  cin >> N;
  cout << N << ":";
  for(auto p : prime_factor(N)) {
    while(p.second--) cout << " " << p.first;
  }
  cout << endl;
}
