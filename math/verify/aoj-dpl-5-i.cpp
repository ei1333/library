int main() {
  int N, K;
  cin >> N >> K;
  cout << stirling_number_second< modint >(N, K) << endl;
}

