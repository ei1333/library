#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_3_D"

#include "../../template/template.cpp"

#include "../../math/number-theory/divisor.cpp"

int main() {
  int A, B, C;
  cin >> A >> B >> C;
  int ret = 0;
  for(auto &p : divisor(C)) {
    ret += A <= p and p <= B;
  }
  cout << ret << "\n";
}
