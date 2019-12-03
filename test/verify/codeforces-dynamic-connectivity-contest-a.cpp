int main() {
  FILE *in, *out;
  in = fopen("connect.in", "r");
  out = fopen("connect.out", "w");

  int N, Q;
  fscanf(in, "%d %d", &N, &Q);
  OfflineDynamicConnectivity odc(N, Q);
  vector< char > T(Q);
  for(int i = 0; i < Q; i++) {
    fscanf(in, " %c", &T[i]);
    if(T[i] == '+' || T[i] == '-') {
      int x, y;
      fscanf(in, "%d %d", &x, &y);
      --x, --y;
      if(T[i] == '+') odc.insert(i, x, y);
      else odc.erase(i, x, y);
    }
  }
  odc.build();
  odc.run([&](int k) {
    if(T[k] == '?') fprintf(out, "%d\n", odc.comp);
  });
}

