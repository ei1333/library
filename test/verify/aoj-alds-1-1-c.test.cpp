// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_1_C

#include "../../template/template.hpp"

#include "../../math/number-theory/is-prime.hpp"

int main() {
  int N;
  cin >> N;
  int ret = 0;
  while(N--) {
    int x;
    cin >> x;
    ret += is_prime(x);
  }
  cout << ret << endl;
}

