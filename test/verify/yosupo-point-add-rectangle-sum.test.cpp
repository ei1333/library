// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/point_add_rectangle_sum

#include "../../template/template.hpp"

#include "../../structure/wavelet/wavelet-matrix-point-add-rectangle-sum.hpp"

#include "../../other/scanner.hpp"
#include "../../other/printer.hpp"

int main() {
  Scanner in(stdin);
  Printer out(stdout);
  int N, Q;
  in.read(N, Q);
  vector< int > x(N), y(N), w(N);
  vector< pair< int, int > > xs;
  xs.reserve(N + Q);
  for(int i = 0; i < N; i++) {
    in.read(x[i], y[i], w[i]);
    xs.emplace_back(x[i], y[i]);
  }
  vector< int > t(Q), a(Q), b(Q), c(Q), d(Q);
  for(int i = 0; i < Q; i++) {
    in.read(t[i], a[i], b[i], c[i]);
    if(t[i] == 0) xs.emplace_back(a[i], b[i]);
    else in.read(d[i]);
  }
  sort(begin(xs), end(xs));
  xs.erase(unique(begin(xs), end(xs)), end(xs));
  vector< int > ys(xs.size());
  for(int i = 0; i < xs.size(); i++) ys[i] = xs[i].second;
  vector< int64 > ws(xs.size());
  for(int i = 0; i < N; i++) {
    x[i] = lower_bound(begin(xs), end(xs), make_pair(x[i], y[i])) - begin(xs);
    ws[x[i]] += w[i];
  }
  for(int i = 0; i < Q; i++) {
    if(t[i] == 0) {
      a[i] = lower_bound(begin(xs), end(xs), make_pair(a[i], b[i])) - begin(xs);
    } else {
      a[i] = lower_bound(begin(xs), end(xs), make_pair(a[i], -1)) - begin(xs);
      c[i] = lower_bound(begin(xs), end(xs), make_pair(c[i], -1)) - begin(xs);
    }
  }
  CompressedWaveletMatrixPointAddRectangleSum< int, 18, int64 > mat(ys, ws);
  for(int i = 0; i < Q; i++) {
    if(t[i] == 0) {
      mat.point_add(a[i], c[i]);
    } else {
      out.writeln(mat.rect_sum(a[i], c[i], b[i], d[i]));
    }
  }
}
