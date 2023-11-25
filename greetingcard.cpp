#include <iostream>
#include <set>

using namespace std;

const int d1 = 1118;
const int d2 = 1680;

struct Point {
  int x, y;
};

bool operator <(Point p, Point q) {
  return p.x < q.x || p.x == q.x && p.y < q.y;
}

size_t countPairs(set<Point> const& points) {
  size_t total = 0;
  for (auto [x, y] : points) {
    total += points.count({ x + 2018, y });
    total += points.count({ x, y + 2018 });
    total += points.count({ x - d1, y + d2 });
    total += points.count({ x + d1, y + d2 });
    total += points.count({ x + d2, y + d1 });
    total += points.count({ x + d2, y - d1 });
  }
  return total;
}

int main() {
  int n;
  cin >> n;

  set<Point> points;
  for (int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    points.insert({ x, y });
  }

  cout << countPairs(points);
}
