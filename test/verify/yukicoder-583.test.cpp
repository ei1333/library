// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/583

#include "../../template/template.hpp"

#include "../../graph/others/eulerian-trail.hpp"

int main() {
  int N, M;
  cin >> N >> M;
  vector< int > A(M), B(M);
  EulerianTrail< false > et(N);
  for(int i = 0; i < M; i++) {
    cin >> A[i] >> B[i];
    et.add_edge(A[i], B[i]);
  }
  if(et.enumerate_semi_eulerian_trail().size() == 1) cout << "YES\n";
  else cout << "NO\n";
}
