#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>

using namespace std;

struct Point {
  double x, y;
};

struct SafePoint : Point {
  double b, root;
};

struct Range {
  double left, bottom, right, top;
};

enum Overlap {
  None, Some, All
};

bool contains(SafePoint s, Point p) {
  double dx = s.x - p.x;
  if (dx < 0) dx = -dx;
  double dy = s.y - p.y;
  if (dy < 0) dy = -dy;
  return dx * dx * dx + dy * dy * dy <= s.b;
}

Overlap overlap(SafePoint s, Range r) {
  if (
    r.left   > s.x + s.root ||
    r.bottom > s.y + s.root ||
    r.right  < s.x - s.root ||
    r.top    < s.y - s.root
  ) {
    return None;
  }

  bool lb = contains(s, Point{ r.left, r.bottom  }),
       lt = contains(s, Point{ r.left, r.top     }),
       rb = contains(s, Point{ r.right, r.bottom }),
       rt = contains(s, Point{ r.right, r.top    });

  if (lb && lt && rb && rt) {
    return All;
  }

  if (
    r.left  > s.x && r.bottom > s.y && !lb ||
    r.left  > s.x && r.top    < s.y && !lt ||
    r.right < s.x && r.bottom > s.y && !rb ||
    r.right < s.x && r.top    < s.y && !rt
  ) {
    return None;
  }

  return Some;
}

int64_t countUnsafe(Range r, vector<SafePoint> const& safe) {
  vector<SafePoint> some;
  some.reserve(safe.size());
  for (auto p : safe) {
    auto o = overlap(p, r);
    if (o == All) {
      return 0;
    }
    else if (o == Some) {
      some.push_back(p);
    }
  }
  if (some.empty()) {
    return (r.right - r.left + 1) * (r.top - r.bottom + 1);
  }
  else {
    double w = int(r.right - r.left + 1) / 2;
    double h = int(r.top - r.bottom + 1) / 2;
    return
      countUnsafe({ r.left,     r.bottom,     r.left + w - 1, r.bottom + h - 1 }, some) +
      countUnsafe({ r.left,     r.bottom + h, r.left + w - 1, r.top            }, some) +
      countUnsafe({ r.left + w, r.bottom,     r.right,        r.bottom + h - 1 }, some) +
      countUnsafe({ r.left + w, r.bottom + h, r.right,        r.top            }, some);
  }
}

int main() {
  double n;
  size_t k;
  cin >> n >> k;
  vector<SafePoint> safe(k);
  for (auto& s : safe) {
    cin >> s.x >> s.y >> s.b;
    s.root = cbrt(s.b);
  }

  cout << countUnsafe({ 0, 0, n, n }, safe) << '\n';
}