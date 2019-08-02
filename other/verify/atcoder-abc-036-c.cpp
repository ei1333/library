int main() {
  int N;
  cin >> N;
  vector< int64 > A(N);
  cin >> A;
  Compress< int64 > comp(A);
  comp.build();
  for(auto &p : comp.get(A)) cout << p << "\n";
}
