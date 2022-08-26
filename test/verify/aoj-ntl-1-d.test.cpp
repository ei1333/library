#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_D"

#include "../../math/number-theory/euler-phi.hpp"
#include "../../template/template.hpp"

int main() {
  int N;
  cin >> N;
  cout << euler_phi< int64_t >(N) << endl;
}
