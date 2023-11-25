#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> dens;

vector<int> solveGreedy() {
  int size = dens[0] + dens[1];
  vector<int> best(size);

  for (int t = 1; t < size; ++t) {
    int rem = t;
    for (int den : dens) {
      best[t] += rem / den;
      rem %= den;
    }
  }

  return best;
}

bool findCounterexample() {
  auto greedy = solveGreedy();
  int size = greedy.size();
  vector<int> best(size);

  for (int t = 1; t < size; ++t) {
    best[t] = t - 1;
    for (int den : dens) {
      if (t >= den && best[t - den] < best[t]) {
        best[t] = best[t - den];
      }
    }
    ++best[t];
    if (best[t] != greedy[t]) {
      return true;
    }
  }
  return false;
}

int main() {
  int n;
  cin >> n;
  dens.resize(n);
  for (auto& den : dens) {
    cin >> den;
  }
  sort(rbegin(dens), rend(dens));
  if (findCounterexample()) {
    cout << "non-";
  }
  cout << "canonical\n";
}