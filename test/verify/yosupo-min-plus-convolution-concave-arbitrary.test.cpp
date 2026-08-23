// clang-format off
// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/min_plus_convolution_concave_arbitrary
// clang-format on

#include <iostream>
#include <vector>

#include "../../dp/min-plus-convolution-concave-arbitary.hpp"

int main() {
  int N, M;
  std::cin >> N >> M;
  std::vector<int> A(N), B(M);
  for (int& a : A) std::cin >> a;
  for (int& b : B) std::cin >> b;
  auto C = min_plus_convolution_concave_arbitary(A, B);
  for (int i = 0; i < static_cast<int>(C.size()); ++i) {
    if (i) std::cout << ' ';
    std::cout << C[i];
  }
  std::cout << '\n';
}
