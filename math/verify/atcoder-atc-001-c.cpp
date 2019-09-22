int main() {
  int N;
  scanf("%d", &N);
  vector< int > A(N + 1), B(N + 1);
  for(int i = 0; i < N; i++) scanf("%d %d", &A[i + 1], &B[i + 1]);
  NumberTheoreticTransform< 1012924417, 5 > ntt;
  auto C = ntt.multiply(A, B);
  for(int i = 1; i <= 2 * N; i++) printf("%d\n", C[i]);
}
