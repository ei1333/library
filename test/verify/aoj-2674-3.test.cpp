// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2674

#include "../../template/template.hpp"

#include "../../structure/segment-tree/segment-tree-fractional-cascading.hpp"

int main() {
  int N, Q;
  cin >> N;
  vector< int64 > X(N);
  for(int i = 0; i < N; i++) {
    cin >> X[i];
  }
  SegmentTreeFractionalCascading seg(X);
  cin >> Q;
  while(Q--) {
    int L, R, E;
    cin >> L >> R >> E;
    --L, --R;
    cout << (R - L + 1) - seg.prod(L, R + 1, min(X[L], X[R]) - E, max(X[L], X[R]) + E + 1) << "\n";
  }
}
