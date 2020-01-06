#define IGNORE

int main() {
  int N, X;
  cin >> N >> X;
  int64 loss = 0;
  vector< int64 > A(N), B(N), C(N);
  vector< int > ord;
  for(int i = 0; i < N; i++) {
    cin >> A[i] >> B[i] >> C[i];
    loss += B[i] * A[i];
    ord.emplace_back(i);
  }
  sort(begin(ord), end(ord), [&](int a, int b) {
    return B[a] > B[b];
  });
 
  auto get_cost = [&](int idx, int64 sum) {
    int64 add = 0;
    add += B[idx] * min(sum, A[idx]);
    add += C[idx] * max(0LL, sum - A[idx]);
    return add;
  };
  MaximumSum< int64 > tap(0);
  for(int i = 0; i < N; i++) {
    tap.insert(get_cost(i, X));
  }
  auto check = [&](int64 sum) {
    int64 need = sum / X;
    tap.set_k(need);
    for(int i : ord) {
      tap.erase(get_cost(i, X));
      bool f = tap.query() + get_cost(i, sum % X) >= loss;
      tap.insert(get_cost(i, X));
      if(f) return true;
    }
    return false;
  };
  int64 ok = 1LL * N * X, ng = -1;
  while(ok - ng > 1) {
    auto mid = (ok + ng) / 2;
    if(check(mid)) ok = mid;
    else ng = mid;
  }
  cout << ok << endl;
}

