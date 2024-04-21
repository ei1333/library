// competitive-verifier: PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_C

#include "../../template/template.hpp"

#include "../../math/matrix/square-matrix.hpp"
#include "../../graph/shortest-path/warshall-floyd.hpp"

int main() {
  int V, E;
  scanf("%d %d", &V, &E);
  SquareMatrix< int, 100 > mat;
  for(int i = 0; i < 100; i++) {
    for(int j = 0; j < 100; j++) {
      if(i != j) mat[i][j] = INT_MAX;
    }
  }
  for(int i = 0; i < E; i++) {
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    mat[x][y] = z;
  }
  warshall_floyd(mat, INT_MAX);
  for(int i = 0; i < V; i++) {
    if(mat[i][i] < 0) {
      puts("NEGATIVE CYCLE");
      return 0;
    }
  }
  for(int i = 0; i < V; i++) {
    for(int j = 0; j < V; j++) {
      if(j > 0) putchar(' ');
      if(mat[i][j] == INT_MAX) printf("INF");
      else printf("%d", mat[i][j]);
    }
    putchar('\n');
  }
}
