int main() {
  int N, K;
  cin >> N >> K;
  cout << get_partition< modint >(N, K)[N][K] << endl;
}
