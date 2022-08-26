#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include "../../structure/wavelet/wavelet-matrix.hpp"
#include "../../template/template.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  vector< int > A(N);
  cin >> A;
  CompressedWaveletMatrix< int, 18 > mat(A);
  for (int i = 0; i < Q; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    cout << mat.kth_smallest(a, b, c) << "\n";
  }
}
