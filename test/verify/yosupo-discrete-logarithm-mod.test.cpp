#define PROBLEM \
  "https://judge.yosupo.jp/problem/discrete_logarithm_mod"

#include "../../math/combinatorics/mod-log.hpp"
#include "../../template/template.hpp"

int main() {
  int T;
  cin >> T;
  while (T--) {
    int64_t X, Y, M;
    cin >> X >> Y >> M;
    cout << mod_log(X, Y, M) << endl;
  }
}
