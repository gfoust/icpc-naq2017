#include <iostream>
#include <string>
using namespace std;

int v(char c) {
  if (c == ' ') return 0;
  else return c - 'a' + 1;
}

int l(int v) {
  if (v == 0) return ' ';
  else return 'a' + v - 1;
}

void encrypt(string& s) {
  int t = 0;
  for (char& c : s) {
    t = (t + v(c)) % 27;
    c = l(t);
  }
}

void decrypt(string& s) {
  int t = 0;
  for (char& c : s) {
    int d = (v(c) - t + 27) % 27;
    t = v(c);
    c = l(d);
  }
}

int main() {
  int n;
  cin >> n;
  cin.ignore(100, '\n');
  for (int i = 0; i < n; ++i) {
    char c = cin.get();
    cin.ignore();
    string s;
    getline(cin, s);
    if (c == 'd') {
      decrypt(s);
    }
    else {
      encrypt(s);
    }
    cout << s << "\n";
  }
}