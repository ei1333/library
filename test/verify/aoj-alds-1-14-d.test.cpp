#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D"

#include "../../template/template.cpp"

#include "../../string/suffix-array.cpp"

int main() {
  string S;
  int Q;

  cin >> S;
  SuffixArray sa(S);
  cin >> Q;
  while(Q--) {
    string T;
    cin >> T;
    auto range = sa.lower_upper_bound(T);
    cout << (range.first != range.second) << endl;
  }
}
