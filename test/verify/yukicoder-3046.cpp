int main() {
  int K, N;
  cin >> K >> N;
  PolynominalMod< modint > X(K + 1);
  X[0] = 1;
  for(int i = 0; i < N; i++) {
    int x;
    cin >> x;
    if(x <= K) X[x] = -1;
  }
  cout << X.inverse()[K] << endl;
}
