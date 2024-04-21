// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_3_C

#include "../../template/template.hpp"

#include "../../dp/largest-rectangle.hpp"

int main() {
  int N;
  cin >> N;
  vector< int > h(N);
  cin >> h;
  cout << largest_rectangle(h) << endl;
}
