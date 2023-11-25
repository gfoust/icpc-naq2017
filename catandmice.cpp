#include <iostream>
#include <iomanip>
#include <queue>
#include <functional>
#include <cmath>
#include <vector>
#include <map>
using namespace std;

using Bits = unsigned int;

struct Mouse {
  double x, y, deadline;
};

struct State {
  Bits remain;
  int last;
};

struct Node {
  int visited, last;
  Bits remain;
  double x, y;
  double distance;
  double velocity;

  operator State() {
    return { remain, last };
  }
};

bool operator <(State a, State b) {
  return a.remain < b.remain || a.remain == b.remain && a.last < b.last;
}

bool operator >(Node const& a, Node const& b) {
  return a.velocity > b.velocity;
}

double distanceBetween(double x1, double y1, double x2, double y2) {
  double dx = x1 - x2;
  double dy = y1 - y2;
  return sqrt(dx*dx + dy*dy);
}

Bits allOn(int n) {
  Bits bits = 0;
  for (int i = 0; i < n; ++i) {
    bits = bits << 1 | 1;
  }
  return bits;
}

struct Search {
  double multiplier;
  vector<Mouse> mice;
  map<State, double> bestV;
  map<State, double> bestD;
  priority_queue<Node, vector<Node>, greater<>> q;

  Search(double multiplier, vector<Mouse> mice) {
    this->multiplier = multiplier;
    this->mice = move(mice);
  }

  double search() {
    q.push({ 0, -1, allOn(mice.size()), 0, 0, 0, 0 });

    while (true) {
      Node node = q.top();
      q.pop();

      if (node.remain == 0) {
        return node.velocity;
      }

      if (bestV[node] == node.velocity || bestD[node] == node.distance) {

        for (int m = 0; m < mice.size(); ++m) {
          auto& mouse = mice[m];
          if (1 << m & node.remain) {
            double newDistance = node.distance +
              distanceBetween(node.x, node.y, mouse.x, mouse.y)
              * pow(multiplier, -node.visited);
            double newVelocity = max(node.velocity, newDistance / mouse.deadline);
            Bits newRemain = node.remain & ~(1 << m);

            Node newNode = {
                node.visited + 1,
                m,
                newRemain,
                mouse.x,
                mouse.y,
                newDistance,
                newVelocity
            };

            auto& oldBestV = bestV[newNode];
            auto& oldBestD = bestD[newNode];
            if (oldBestV == 0 || oldBestD == 0 || oldBestV > newVelocity || oldBestD > newDistance) {
              oldBestV = newVelocity;
              oldBestD = newDistance;
              q.push(newNode);
            }
          }
        }

      }
    }

    return -1;
  }
};

int main() {
  int numMice;
  cin >> numMice;
  vector<Mouse> mice(numMice);
  for (auto& mouse : mice) {
    cin >> mouse.x >> mouse.y >> mouse.deadline;
  }
  double multiplier;
  cin >> multiplier;

  Search search(multiplier, move(mice));
  cout << setprecision(5) << fixed << search.search() << '\n';
}
