#include <bits/stdc++.h>
using namespace std;
#define main moin
#define $END$
#include "../../template/template.cpp"
#undef $END$
#undef main

#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D"
#include "../longest-increasing-subsequence.cpp"

int main() {
  int N;
  cin >> N;
  vector< int > A(N);
  cin >> A;
  cout << longest_increasing_subsequence(A, true) << endl;
}

