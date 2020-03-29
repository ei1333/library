#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0225"

#include "../../template/template.cpp"

#include "../../graph/graph-template.cpp"

#include "../../graph/others/eulerian-trail.cpp"

int main() {
  int N;
  while(cin >> N, N) {
    Edges< int > es;
    for(int i = 0; i < N; i++) {
      string s;
      cin >> s;
      es.emplace_back(s.front() - 'a', s.back() - 'a');
    }
    auto path = eulerian_trail(es, true);
    if(path.empty() || path.front().from != path.back().to) {
      cout << "NG\n";
    } else {
      cout << "OK\n";
    }
  }
}
