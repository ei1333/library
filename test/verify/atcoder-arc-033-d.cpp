#define IGNORE

int main() {
  int N, T;
  cin >> N;
  vector< modint > A(N + 1);
  cin >> A;
  cin >> T;
  cout << lagrange_polynomial(A, T) << endl;
}
