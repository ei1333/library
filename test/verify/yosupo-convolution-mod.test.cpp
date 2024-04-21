// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/convolution_mod

#include "../../template/template.hpp"

#include "../../math/fft/number-theoretic-transform.hpp"

int main() {
  int N, M;
  cin >> N >> M;
  vector< int > A(N), B(M);
  for(auto &a : A) cin >> a;
  for(auto &b : B) cin >> b;
  NumberTheoreticTransform< 998244353 > ntt;
  for(auto &c : ntt.multiply(A, B)) cout << c << " ";
  cout << endl;
}
