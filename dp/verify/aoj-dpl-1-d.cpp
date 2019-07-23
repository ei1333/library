int main() {
  int N;
  cin >> N;
  vector< int > A(N);
  cin >> A;
  cout << longest_increasing_subsequence(A, true) << endl;
}

