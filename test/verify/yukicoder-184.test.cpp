// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/184

#include "../../template/template.hpp"

#include "../../math/matrix/binary-basis.hpp"

int main() {
  int N;
  cin >> N;
  BinaryBasis< int64 > bb;
  for(int i = 0; i < N; i++) {
    int64 x;
    cin >> x;
    bb.add(x);
  }
  cout << (1LL << bb.size()) << "\n";
}
