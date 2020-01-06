#define IGNORE

int main() {
  int N;
  cin >> N;
  vector< int64_t > A(N);
  for(int i = 0; i < N; i++) cin >> A[i];
  constexpr int64_t INF = 1LL << 60;
  cout << hu_tucker< SkewHeap< int64_t > >(A, INF) << endl;
}
