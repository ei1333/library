#define PROBLEM "https://judge.yosupo.jp/problem/kth_root_integer"

#include "../../template/template.cpp"

#include "../../math/number-theory/kth-root-integer.cpp"

int main() {
  int T;
  cin >> T;
  while(T--) {
    uint64_t a;
    int k;
    cin >> a >> k;
    cout << kth_root_integer(a, k) << "\n";
  }
}
