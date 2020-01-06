#define IGNORE

int main() {
  int N, M;
  cin >> N >> M;
  PolynominalMod< modint > C(M + 1);
  C[0] = 1;
  for(int i = 0; i < N; i++) {
    int k;
    cin >> k;
    if(k <= M) C[k] = mod - 4;
  }
  C = C.sqrt();
  C[0] += 1;
  C = C.inverse();
  for(int i = 1; i <= M; i++) {
    cout << C[i] * 2 << "\n";
  }
}
