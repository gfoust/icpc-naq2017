#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;
template <typename T>
using Array = vector<T>;

struct Vector {
  double x, y;
};

struct Point {
  double x, y;
};

Vector operator -(Point p, Point q) {
  return { p.x - q.x, p.y - q.y };
}

Vector operator /(Vector v, double s) {
  return { v.x / s, v.y / s };
}

Vector operator *(Vector v, double s) {
  return { v.x * s, v.y * s };
}

Point& operator +=(Point& p, Vector v) {
  p.x += v.x;
  p.y += v.y;
  return p;
}

bool operator !=(Point p, Point q) {
  return p.x != q.x || p.y != q.y;
}

double distance(Point p, Point q) {
  double dx = p.x - q.x;
  double dy = p.y - q.y;
  return sqrt(dx*dx + dy*dy);
}

double distance(vector<Point> const& ps) {
  double d = 0;
  for (int i = 1; i < ps.size(); ++i) {
    d += distance(ps[i - 1], ps[i]);
  }
  return d;
}

int main() {
  int n, interval;
  cin >> n >> interval;

  Array<Point> actual(n);
  Array<double> times(n);
  for (int i = 0; i < n; ++i) {
    cin >> actual[i].x >> actual[i].y >> times[i];
  }

  Array<Point> gps;
  gps.push_back(actual.front());
  double t = 0, tnext = interval;
  Point p = actual[0];
  Vector v = (actual[1] - actual[0]) / times[1];
  int i = 1;
  while (i < n) {
    if (tnext >= times[i]) {
      if (tnext == times[i]) {
        gps.push_back(actual[i]);
        tnext += interval;
      }
      p = actual[i];
      t = times[i];
      if (i < n - 1) {
        v = (actual[i + 1] - actual[i]) / (times[i + 1] - times[i]);
      }
      ++i;
    }
    else {
      p += v * (tnext - t);
      gps.push_back(p);
      t = tnext;
      tnext += interval;
    }
  }
  if (gps.back() != actual.back()) {
    gps.push_back(actual.back());
  }

  double x = distance(gps);
  double y = distance(actual);
  cout << setprecision(7) << fixed <<  (y - x) / y * 100.0 << "\n";
}