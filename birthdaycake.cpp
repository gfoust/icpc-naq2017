#include <iostream>
#include <vector>
#include <optional>

using namespace std;

struct Point {
  double x, y;
};

struct Vector {
  double x, y;
};

Point operator +(Point p, Vector v) {
  return { p.x + v.x, p.y + v.y };
}

Vector operator -(Point p, Point q) {
  return { p.x - q.x, p.y - q.y };
}

Vector operator *(double s, Vector v) {
  return { s * v.x, s * v.y };
}

double dot(Vector v, Vector w) {
  return v.x * w.x + v.y * w.y;
}

double cross(Vector v, Vector w) {
  return v.x * w.y - v.y * w.x;
}

struct Line {
  Point p;
  Vector v;

  Point at(double t) {
    return p + t * v;
  }
};

Line fromEquation(double a, double b, double c) {
  Point p; Vector v;
  if (b == 0) {
    p = { -c / a, 0 };
    v = { 0, 1 };
  }
  else {
    p = { 0, -c / b };
    v = { b, -a };
  }
  return { p, v };
}

optional<Point> intersection(Line k, Line l) {
  double t, a = cross(k.v, l.v);
  if (a == 0) {
    return {};
  }
  else {
    t = cross(l.p - k.p, l.v) / a;
    return k.at(t);
  }
}

bool separates(Point p, Point q, Line l) {
  return cross(l.v, p - l.p) > 0 != cross(l.v, q - l.p) > 0;
}


vector<Point> candles;
vector<Line> cuts;
double radius;

int countPieces() {
  int count = 1 + cuts.size();
  const Point origin = { 0 , 0 };
  const double radiusSquare = radius * radius;
  for (int i = 0; i < cuts.size(); ++i) {
    for (int j = i + 1; j < cuts.size(); ++j) {
      auto p = intersection(cuts[i], cuts[j]);
      if (p && dot(*p - origin, *p - origin) < radiusSquare) {
        ++count;
      }
    }
  }
  return count;
}

bool allCandlesDistinct() {
  for (int i = 0; i < candles.size(); ++i) {
    for (int j = i + 1; j < candles.size(); ++j) {
      bool separated = false;
      for (auto const& cut : cuts) {
        if (separates(candles[i], candles[j], cut)) {
          separated = true;
          break;
        }
      }
      if (!separated) return false;
    }
  }
  return true;
}

int main() {
  int n, m;
  cin >> n >> m >> radius;

  candles.resize(n);
  for (auto& candle : candles) {
    cin >> candle.x >> candle.y;
  }

  cuts.resize(m);
  for (auto& cut : cuts) {
    double a, b, c;
    cin >> a >> b >> c;
    cut = fromEquation(a, b, c);
  }

  if (countPieces() == candles.size() && allCandlesDistinct()) {
    cout << "yes\n";
  }
  else {
    cout << "no\n";
  }
}