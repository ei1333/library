// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D

#include "../../template/template.hpp"

#include "../../dp/longest-increasing-subsequence.hpp"

int main() {
  int N;
  cin >> N;
  vector< int > A(N);
  cin >> A;
  cout << longest_increasing_subsequence(A, true) << endl;
}
