#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"

#include "../../template/template.cpp"

#include "../../math/combinatorics/mod-int.cpp"

#include "../../math/matrix/matrix.cpp"

const int MOD = 998244353;
using mint = ModInt< MOD >;

int main() {
  int N;
  cin >> N;
  Matrix< mint > mat(N);
  for(int i = 0; i < N; i++) cin >> mat[i];
  cout << mat.determinant() << endl;
}
