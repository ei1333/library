#define PROBLEM "https://judge.yosupo.jp/problem/range_kth_smallest"

#include "../../template/template.cpp"

#include "../../structure/wavelet/succinct-indexable-dictionary.cpp"
#include "../../structure/wavelet/wavelet-tree.cpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  vector< int > A(N);
  cin >> A;
  CompressedWaveletTree< int, 18 > mat(A);
  for(int i = 0; i < Q; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    cout << mat.kth_smallest(a, b, c) << "\n";
  }
}
