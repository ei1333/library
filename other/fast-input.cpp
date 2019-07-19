template< int sz >
struct FastInput {
  char buf[sz + 1];
  char *o;

  FastInput() { init(); }

  void init() {
    o = buf;
    buf[fread(buf, sizeof(char), sizeof(char) * sz, stdin)] = '\0';
  }

  int64_t read() {
    int64_t ret = 0, sign = 1;
    while(*o && *o <= 32) ++o;
    if(*o == '-') sign *= -1, ++o;
    while(*o >= '0' && *o <= '9') {
      ret *= 10;
      ret += *o++ - '0';
    }
    return ret * sign;
  }
};
