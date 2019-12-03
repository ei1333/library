nt main() {
  int N, Q;
  cin >> N;
  vector< int > A(N);
  for(int i = 0; i < N; i++) {
    cin >> A[i];
  }
  cin >> Q;
  vector< int > f(1000001);
  Mo mo(N, Q);
  for(int i = 0; i < Q; i++) {
    int l, r;
    cin >> l >> r;
    mo.add(--l, r);
  }
  int ret = 0;
  auto add = [&](int idx) { if(f[A[idx]]++ == 0) ret++; };
  auto del = [&](int idx) { if(f[A[idx]]-- == 1) --ret; };
  vector< int > ans(Q);
  auto rem = [&](int idx) { ans[idx] = ret; };
  mo.run(add, del, rem);
  for(int i = 0; i < Q; i++) {
    cout << ans[i] << "\n";
  }
}
