// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1163

#include "../../template/template.hpp"

#include "../../graph/flow/hungarian.hpp"

int main() {
  int M, N, B[500], R[500];
  while(cin >> M >> N, M) {
    for(int i = 0; i < M; i++) {
      cin >> B[i];
    }
    for(int i = 0; i < N; i++) {
      cin >> R[i];
    }
    if(M > N) swap(M, N), swap(B, R);
    Matrix< int > mat(M + 1, N + 1);
    for(int i = 0; i < M; i++) {
      for(int j = 0; j < N; j++) {
        if(__gcd(B[i], R[j]) > 1) mat[i + 1][j + 1] = -1;
      }
    }
    cout << -hungarian(mat).first << endl;
  }
}
