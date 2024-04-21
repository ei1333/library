// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1236

#include "../../template/template.hpp"

#include "../../math/rational/rational.hpp"

int main() {
  string s, t;
  cin >> s >> t;
  int a = stoi(s);
  int b = stoi(t);
  using F = Rational< int >;
  F c(a * 60 + b);
  F d(720, 11);
  F x(0);
  while(x < c) x += d;
  x = x - c;
  cout << x.numerator() * 60 / x.denominator() << "\n";
}
