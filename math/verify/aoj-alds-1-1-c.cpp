int main() {
  int N;
  cin >> N;
  int ret = 0;
  while(N--) {
    int x;
    cin >> x;
    ret += is_prime(x);
  }
  cout << ret << endl;
}

