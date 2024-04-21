// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2603

#include "../../template/template.hpp"

#include "../../dp/divide-and-conquer-optimization.hpp"

int main() {
  int S, N, M;
  cin >> S >> N >> M;
  vector< int > X(S);
  cin >> X;
  vector< int > T(N);
  for(int i = 0; i < N; i++) {
    int a, b;
    cin >> a >> b;
    T[i] = a - X[--b];
  }
  sort(begin(T), end(T));
  auto mat = make_v< int >(N, N);
  for(int right = N - 1; right >= 0; right--) {
    for(int left = right - 1; left >= 0; left--) {
      mat[left][right] = mat[left + 1][right] + T[right] - T[left];
    }
  }
  auto val = divide_and_conquer_optimization< int >(M, N, inf, [&](int a, int b) { return mat[a][b - 1]; });
  int ret = inf;
  for(int k = 0; k < val.size(); k++) chmin(ret, val[k].back());
  cout << ret << "\n";
}
