// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_1_C

#include "../../template/template.hpp"

#include "../../math/number-theory/prime-table.hpp"

int main() {
  auto t = prime_table(100000000);
  int N;
  cin >> N;
  int ret = 0;
  while(N--) {
    int x;
    cin >> x;
    ret += t[x];
  }
  cout << ret << endl;
}
