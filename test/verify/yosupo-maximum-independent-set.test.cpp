#define PROBLEM \
  "https://judge.yosupo.jp/problem/maximum_independent_set"

#include "../../graph/others/maximum-independent-set.hpp"
#include "../../math/matrix/matrix.hpp"
#include "../../template/template.hpp"

int main() {
  int N, M;
  cin >> N >> M;
  Matrix< bool > mat(N);
  for (int i = 0; i < M; i++) {
    int a, b;
    cin >> a >> b;
    mat[a][b] = true;
    mat[b][a] = true;
  }
  auto ret = maximum_independent_set(mat);
  cout << ret.size() << endl;
  cout << ret << endl;
}
