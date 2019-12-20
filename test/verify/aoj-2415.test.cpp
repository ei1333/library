#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2415"

#include "../../template/template.cpp"

#include "../../dp/hu-tucker.cpp"

#include "../../structure/heap/skew-heap.cpp"

int main() {
  int N;
  cin >> N;
  vector< int64_t > A(N);
  for(int i = 0; i < N; i++) cin >> A[i];
  cout << hu_tucker< SkewHeap< int64_t >, int64_t >(A, 1LL << 60) << endl;
}
