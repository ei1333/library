// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_D

#include "../../template/template.hpp"

#include "../../math/number-theory/euler-phi.hpp"

int main() {
  int N;
  cin >> N;
  cout << euler_phi< int64_t >(N) << endl;
}
