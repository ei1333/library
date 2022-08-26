#define PROBLEM                            \
  "http://judge.u-aizu.ac.jp/onlinejudge/" \
  "description.jsp?id=ALDS1_14_D"

#include "../../string/suffix-array.hpp"
#include "../../template/template.hpp"

int main() {
  string S;
  int Q;

  cin >> S;
  SuffixArray sa(S);
  cin >> Q;
  while (Q--) {
    string T;
    cin >> T;
    auto range = sa.equal_range(T);
    cout << (range.first != range.second) << endl;
  }
}
