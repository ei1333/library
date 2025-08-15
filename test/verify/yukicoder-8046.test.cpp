// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/8046

#include "../../template/template.hpp"

#include "../../math/combinatorics/montgomery-mod-int.hpp"
#include "../../math/fps/formal-power-series.hpp"

using mint = modint1000000007;

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
