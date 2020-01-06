#define IGNORE

int main() {
  int N;
  cin >> N;
  vector< int64_t > A(N);
  for(auto &p : A) cin >> p;
  function< int64_t(int, int) > f = [&](int i, int j) { return A[j] + 1LL * (j - i) * (j - i); };
  for(auto &p : monotone_minima(N, N, f)) cout << p.second << endl;
}

