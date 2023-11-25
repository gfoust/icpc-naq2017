#include <iostream>
#include <queue>
#include <map>
#include <set>
#include <vector>
#include <functional>

using namespace std;
using uint = unsigned int;

struct State {
  int city;
  uint cost;
  bool canfly;
};

bool operator >(State a, State b) {
  return a.cost > b.cost;
}

struct Graph {
  map<int, map<int, uint>> roads;
  map<int, set<int>> flights;

  uint search(int start, int finish) {
    map<int, uint> best;
    priority_queue<State, vector<State>, greater<State>> discovered;
    best[start] = 0;
    discovered.push({ start, 0, true });

    while (!discovered.empty()) {
      auto [city, cost, canfly] = discovered.top();
      discovered.pop();
      if (cost == best[city]) {
        if (city == finish) {
          return cost;
        }
        for (auto [next, roadcost] : roads[city]) {
          uint nextcost = cost + roadcost;
          auto [p, inserted] = best.insert({ next, nextcost });
          if (inserted || nextcost < p->second) {
            p->second = nextcost;
            discovered.push({ next, nextcost, canfly });
          }
        }
      }
      if (canfly) {
        for (auto next : flights[city]) {
          auto [p, inserted] = best.insert({ next, cost });
          if (inserted || cost < p->second) {
            p->second = cost;
            discovered.push({ next, cost, false });
          }
        }
      }
    }
    return -1;
  }
};

int main() {
  Graph graph;
  int n, m, f, s, t;
  cin >> n >> m >> f >> s >> t;

  for (int i = 0; i < m; ++i) {
    int a, b, c;
    cin >> a >> b >> c;
    graph.roads[a][b] = c;
    graph.roads[b][a] = c;
  }

  for (int i = 0; i < f; ++i) {
    int a, b;
    cin >> a >> b;
    graph.flights[a].insert(b);
  }

  cout << graph.search(s, t) << "\n";
}
