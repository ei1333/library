int main() {
  int N;
  cin >> N;
  cout << N << ":";
  for(auto p : prime_factor(N)) {
    while(p.second--) cout << " " << p.first;
  }
  cout << endl;
}
