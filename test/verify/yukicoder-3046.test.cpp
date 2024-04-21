// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/3046

#include "../../template/template.hpp"

#include "../../math/combinatorics/mod-int.hpp"
#include "../../math/fps/formal-power-series.hpp"

const int MOD = (int)(1e9 + 7);
using mint = ModInt< MOD >;

int main() {
  int K, N;
  cin >> K >> N;
  FPS< mint > X(K + 1);
  X[0] = 1;
  for(int i = 0; i < N; i++) {
    int x;
    cin >> x;
    if(x <= K) X[x] = -1;
  }
  cout << X.inv()[K] << endl;
}
