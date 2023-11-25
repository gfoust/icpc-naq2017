#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
  double d, s;
  cin >> d >> s;

  double a = 500'000'000;
  double i = a / 2;
  while (i >= 0.0000000001) {
    if (a + s - a * cosh(d / 2 / a) > 0) {
      a -= i;
    }
    else {
      a += i;
    }
    i /= 2;
  }

  cout << fixed << 2 * a * sinh(d / 2 / a);
}