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
