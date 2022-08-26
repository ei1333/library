#define PROBLEM \
  "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_I"

#include "../../math/combinatorics/mod-int.hpp"
#include "../../math/combinatorics/stirling-number-second.hpp"
#include "../../template/template.hpp"

int main() {
  int N, K;
  cin >> N >> K;
  cout << stirling_number_second< modint >(N, K) << endl;
}
