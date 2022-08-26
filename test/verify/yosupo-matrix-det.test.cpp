#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"

#include "../../math/combinatorics/mod-int.hpp"
#include "../../math/matrix/matrix.hpp"
#include "../../template/template.hpp"

const int MOD = 998244353;
using mint    = ModInt< MOD >;

int main() {
  int N;
  cin >> N;
  Matrix< mint > mat(N);
  for (int i = 0; i < N; i++) cin >> mat[i];
  cout << mat.determinant() << endl;
}
