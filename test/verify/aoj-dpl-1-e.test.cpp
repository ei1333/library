#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_E"

#include "../../template/template.cpp"

#include "../../dp/edit-distance.cpp"

int main() {
  string S, T;
  cin >> S >> T;
  cout << edit_distance(S, T) << endl;
}

