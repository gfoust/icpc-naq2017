#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Range {
  double start, finish;
};

int main() {
  int numMeasures, numIntervals;
  double startTime, endTime;
  cin >> numMeasures >> numIntervals >> startTime >> endTime;

  vector<double> measures(numMeasures);
  for (auto& m : measures) {
    cin >> m;
  }

  vector<Range> intervals(numIntervals);
  for (auto& i : intervals) {
    cin >> i.start >> i.finish;
  }

  vector<Range> bad;
  for (auto m : measures) {
    for (auto [s, f] : intervals) {
      Range b = { max(s - m, startTime), min(f - m, endTime) };
      if (b.start < b.finish) {
        bad.push_back(b);
      }
    }
  }

  sort(begin(bad), end(bad), [](Range a, Range b) { return a.start < b.start; });

  double total = 0;
  Range cur = { -1, -1 };
  for (auto b : bad) {
    if (b.start <= cur.finish) {
      cur.finish = max(cur.finish, b.finish);
    }
    else {
      total += cur.finish - cur.start;
      cur = b;
    }
  }
  total += cur.finish - cur.start;
  double full = endTime - startTime;
  cout << (full - total) / full;

}