#include <iostream>
using namespace std;

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int g, j, l;
    cin >> g >> l;
    for (j = 2; j <= g; ++j) {
      int k;
      cin >> k;
      if (k != l + 1) {
        cout << j++ << "\n";
        break;
      }
      l = k;
    }
    for (; j <= g; ++j) {
      int k;
      cin >> k;
    }
  }
}