#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

#include "../../template/template.cpp"

#include "../../math/number-theory/fast-prime-factorization.cpp"

int main() {
  int Q;
  cin >> Q;
  while(Q--) {
    int64 X;
    cin >> X;
    auto ret = FastPrimeFactorization::prime_factor(X);
    sort(begin(ret), end(ret));
    cout << ret.size() << " ";
    cout << ret << "\n";
  }
}
