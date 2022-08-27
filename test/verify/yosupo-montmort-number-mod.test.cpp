#define PROBLEM "https://judge.yosupo.jp/problem/montmort_number_mod"

#include "../../math/combinatorics/arbitrary-mod-int.hpp"
#include "../../math/combinatorics/montmort.hpp"
#include "../../template/template.hpp"

int main() {
  int N, M;
  cin >> N >> M;
  ArbitraryModInt::set_mod(M);
  auto ret = montmort< ArbitraryModInt >(N);
  ret.erase(begin(ret));
  cout << ret << endl;
}
