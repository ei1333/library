// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/rectangle_sum

#include "../../template/template.hpp"

#include "../../structure/wavelet/succinct-indexable-dictionary.hpp"
#include "../../structure/wavelet/wavelet-matrix-rectangle-sum.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  vector< int > x(N), y(N), w(N);
  vector< pair< int, int > > xs(N);
  for(int i = 0; i < N; i++) {
    cin >> x[i] >> y[i] >> w[i];
    xs[i] = {x[i], i};
  }
  sort(begin(xs), end(xs));
  vector< int > ys(N);
  vector< int64 > ws(N);
  for(int i = 0; i < N; i++) {
    x[i] = lower_bound(begin(xs), end(xs), make_pair(x[i], i)) - begin(xs);
    ys[x[i]] = y[i];
    ws[x[i]] = w[i];
  }
  CompressedWaveletMatrixRectangleSum< int, 18, int64 > mat(ys, ws);
  while(Q--) {
    int l, r, d, u;
    cin >> l >> d >> r >> u;
    l = lower_bound(begin(xs), end(xs), make_pair(l, -1)) - begin(xs);
    r = lower_bound(begin(xs), end(xs), make_pair(r, -1)) - begin(xs);
    cout << mat.rect_sum(l, r, d, u) << "\n";
  }
}

