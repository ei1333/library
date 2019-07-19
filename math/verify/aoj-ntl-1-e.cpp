int main() {
  int a, b, x, y;
  cin >> a >> b;
  extgcd(a, b, x, y);
  cout << x << " " << y << endl;
}
