#define PROBLEM "https://judge.yosupo.jp/problem/montmort_number_mod"

#include "../../template/template.cpp"

#include "../../math/combinatorics/arbitrary-mod-int.cpp"
#include "../../math/combinatorics/montmort.cpp"

int main() {
  int N, M;
  cin >> N >> M;
  ArbitraryModInt::set_mod(M);
  auto ret = montmort< ArbitraryModInt >(N);
  ret.erase(begin(ret));
  cout << ret << endl;
}
