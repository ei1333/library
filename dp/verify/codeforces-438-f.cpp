int main() {
  int N, K;
  cin >> N >> K;
  vector< int > A(N);
  for(int i = 0; i < N; i++) {
    cin >> A[i];
    --A[i];
  }
  constexpr int64_t INF = 1LL << 58;

  int64 L = 0, R = 0, sum = 0;
  vector< int > appear(100000);
  auto add = [&](int idx) { sum += appear[A[idx]]++; };
  auto del = [&](int idx) { sum -= --appear[A[idx]]; };
  function< int64_t(int l, int r) > f = [&](int l, int r) {
    while(L > l) add(--L);
    while(R < r) add(R++);
    while(L < l) del(L++);
    while(R > r) del(--R);
    return sum;
  };
  cout << divide_and_conquer_optimization(K, N, INF, f).back().back() << endl;
}

