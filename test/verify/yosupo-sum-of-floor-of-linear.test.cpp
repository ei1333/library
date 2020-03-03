#define PROBLEM "https://judge.yosupo.jp/problem/sum_of_floor_of_linear"

#include "../../template/template.cpp"

#include "../../math/number-theory/sum-of-floor-of-linear.cpp"

int main() {
  int T;
  cin >> T;
  while(T--) {
    int64 N, M, A, B;
    cin >> N >> M >> A >> B;
    cout << sum_of_floor_of_linear(N, M, A, B) << "\n";
  }
}
