int main() {
  int N;
  cin >> N;
  vector< modint > A(N + 1), B(N + 1);
  for(int i = 1; i <= N; i++) cin >> A[i] >> B[i];
  ArbitraryModConvolution< modint > fft;
  auto C = fft.multiply(A, B);
  for(int i = 1; i <= 2 * N; i++) cout << C[i] << "\n";
}
