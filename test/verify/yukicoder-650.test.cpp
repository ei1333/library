// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/650

#include "../../template/template.hpp"

#include "../../graph/tree/heavy-light-decomposition.hpp"

#include "../../structure/segment-tree/segment-tree.hpp"

#include "../../math/combinatorics/mod-int.hpp"
#include "../../math/matrix/square-matrix.hpp"

int main() {
  int N;
  cin >> N;
  vector< int > X(N), Y(N);
  HeavyLightDecomposition<> g(N);
  for(int i = 1; i < N; i++) {
    cin >> X[i] >> Y[i];
    g.add_edge(X[i], Y[i]);
  }
  g.build();
  for(int i = 1; i < N; i++) {
    if(g.in[X[i]] > g.in[Y[i]]) swap(X[i], Y[i]);
  }
  using Mat = SquareMatrix< modint, 2 >;
  auto f = [](const Mat &a, const Mat &b) { return a * b; };
  auto seg = get_segment_tree(N, f, Mat::mul_identity());
  int Q;
  cin >> Q;
  while(Q--) {
    char x;
    cin >> x;
    if(x == 'x') {
      int v;
      cin >> v;
      Mat m;
      cin >> m[0][0] >> m[0][1] >> m[1][0] >> m[1][1];
      seg.set(g.in[Y[v + 1]], m);
    } else {
      int y, z;
      cin >> y >> z;
      auto mat = g.query(y, z, Mat::mul_identity(), [&](int a, int b) { return seg.prod(a, b); }, f, true);
      cout << mat[0][0] << " " << mat[0][1] << " " << mat[1][0] << " " << mat[1][1] << "\n";
    }
  }
}
