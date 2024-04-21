// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/line_add_get_min

#include "../../template/template.hpp"

#include "../../structure/convex-hull-trick/dynamic-li-chao-tree.hpp"

int main() {
  int N, Q;
  cin >> N >> Q;
  const int64 MAX_P = 1000000000;
  DynamicLiChaoTree< int64, -MAX_P, MAX_P, infll > cht;
  for(int i = 0; i < N; i++) {
    int64 a, b;
    cin >> a >> b;
    cht.add_line(a, b);
  }
  while(Q--) {
    int T;
    cin >> T;
    if(T == 0) {
      int64 A, B;
      cin >> A >> B;
      cht.add_line(A, B);
    } else {
      int64 P;
      cin >> P;
      cout << cht.query(P) << "\n";
    }
  }
}
