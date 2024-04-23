// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/matrix_det

#include "../../template/template.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"

#include "../../math/matrix/matrix.hpp"

using mint = modint998244353;

int main() {
  int N;
  cin >> N;
  Matrix< mint > mat(N);
  for(int i = 0; i < N; i++) cin >> mat[i];
  cout << mat.determinant() << endl;
}
