#define PROBLEM                            \
  "http://judge.u-aizu.ac.jp/onlinejudge/" \
  "description.jsp?id=ALDS1_1_C"

#include "../../math/number-theory/is-prime.hpp"
#include "../../template/template.hpp"

int main() {
  int N;
  cin >> N;
  int ret = 0;
  while (N--) {
    int x;
    cin >> x;
    ret += is_prime(x);
  }
  cout << ret << endl;
}
