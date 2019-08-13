#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_I"

#include "../../template/template.cpp"

#include "../mod-int.cpp"
#include "../combination.cpp"

#include "../stirling-number-second.cpp"

int main() {
  int N, K;
  cin >> N >> K;
  cout << stirling_number_second< modint >(N, K) << endl;
}

