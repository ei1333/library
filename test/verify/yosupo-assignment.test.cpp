// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/assignment

#include "../../template/template.hpp"

#include "../../graph/flow/hungarian.hpp"

int main() {
  int N;
  cin >> N;
  Matrix< int64_t > X(N + 1, N + 1);
  for(int i = 1; i <= N; i++) {
    for(int j = 1; j <= N; j++) {
      cin >> X[j][i];
    }
  }
  auto ret = hungarian(X);
  cout << ret.first << "\n";
  ret.second.erase(begin(ret.second));
  for(auto& p : ret.second) --p;
  cout << ret.second << "\n";
}
