#define PROBLEM "https://yukicoder.me/problems/no/583"

#include "../../template/template.cpp"

#include "../../graph/graph-template.cpp"
#include "../../graph/others/eulerian-trail.cpp"

int main() {
  int N, M;
  cin >> N >> M;
  vector< int > A(M), B(M);
  vector< int > used(N);
  for(int i = 0; i < M; i++) {
    cin >> A[i] >> B[i];
    used[A[i]] = true;
    used[B[i]] = true;
  }
  int ptr = 0;
  for(int i = 0; i < N; i++) {
    if(used[i]) used[i] = ptr++;
  }
  Edges<> es;
  for(int i = 0; i < M; i++) {
    es.emplace_back(used[A[i]], used[B[i]]);
  }
  if(eulerian_trail(es, false).empty()) cout << "NO\n";
  else cout << "YES\n";
}
