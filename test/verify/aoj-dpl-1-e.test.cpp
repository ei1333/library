// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_E

#include "../../template/template.hpp"

#include "../../dp/edit-distance.hpp"

int main() {
  string S, T;
  cin >> S >> T;
  cout << edit_distance(S, T) << endl;
}

