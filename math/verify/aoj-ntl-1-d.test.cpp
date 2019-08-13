#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_D"

#include "../../template/template.cpp"

#include "../euler-phi.cpp"

int main() {
  int N;
  cin >> N;
  cout << euler_phi(N) << endl;
}
