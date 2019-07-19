int main() {
  int N, Q;
  while(cin >> N, N) {
    cin >> Q;
    vector< int > A(N);
    for(int i = 0; i < N; i++) {
      cin >> A[i];
      A[i] += 100000;
    }
    vector< int > f(200001), g(200001);
    Mo mo(N, Q);
    for(int i = 0; i < Q; i++) {
      int l, r;
      cin >> l >> r;
      mo.add(--l, r);
    }
    int ret = 0;
    auto add = [&](int idx) {
      g[f[A[idx]]]--;
      f[A[idx]]++;
      g[f[A[idx]]]++;
      if(f[A[idx]] > ret) ++ret;
    };
    auto del = [&](int idx) {
      g[f[A[idx]]]--;
      f[A[idx]]--;
      g[f[A[idx]]]++;
      if(ret - 1 == f[A[idx]] && g[ret] == 0) --ret;
    };
    vector< int > ans(Q);
    auto rem = [&](int idx) { ans[idx] = ret; };
    mo.run(add, del, rem);
    for(int i = 0; i < Q; i++) {
      cout << ans[i] << "\n";
    }
  }
}
