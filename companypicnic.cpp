#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

vector<string> employees;
vector<double> speeds;
vector<vector<int>> under;

struct Score {
  int teams = 0;
  double speed = 0;
};

bool operator <(Score a, Score b) {
  return a.teams < b.teams || a.teams == b.teams && a.speed < b.speed;
}

Score& operator +=(Score& a, Score b) {
  a.teams += b.teams;
  a.speed += b.speed;
  return a;
}

vector<bool> visited;
vector<Score> bestWith;
vector<Score> bestWithout;

int id(string const& name) {
  auto p = find(begin(employees), end(employees), name);
  if (p == end(employees)) {
    employees.push_back(name);
    speeds.push_back(0);
    under.push_back({});
    return employees.size() - 1;
  }
  else {
    return p - begin(employees);
  }
}

void visit(int id) {
  if (!visited[id]) {
    visited[id] = true;
    auto& underid = under[id];
    
    Score wo;
    vector<Score> w(underid.size());
    for (int i = 0; i < underid.size(); ++i) {
      int u = underid[i];
      visit(u);
      wo += bestWith[u];
      for (int j = 0; j < underid.size(); ++j) {
        if (i != j) {
          w[j] += bestWith[u];
        }
        else {
          w[j] += bestWithout[u];
          w[j] += { 1, min(speeds[u], speeds[id]) };
        }
      }
    }

    if (w.size() > 0) {
      bestWith[id] = *max_element(begin(w), end(w));
      bestWithout[id] = wo;
      bestWith[id] = max(bestWith[id], bestWithout[id]);
    }
  }
}

int main() {
  int n;
  cin >> n;
  employees.reserve(n);
  speeds.reserve(n);
  under.reserve(n);
  int ceo = 0;
  for (int i = 0; i < n; ++i) {
    string n, b;
    double s;
    cin >> n >> s >> b;
    int nid = id(n);
    speeds[nid] = s;
    if (b == "CEO") {
      ceo = nid;
    }
    else {
      int bid = id(b);
      under[bid].push_back(nid);
    }
  }

  visited.resize(n);
  bestWith.resize(n);
  bestWithout.resize(n);
  visit(ceo);
  Score best = max(bestWith[ceo], bestWithout[ceo]);
  cout << best.teams << ' ' << fixed << best.speed / best.teams << '\n';
}