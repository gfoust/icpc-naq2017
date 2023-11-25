#include <iostream>
#include <vector>
#include <tuple>
#include <stdexcept>

using namespace std;

enum class In {
  Forward,
  Left,
  Right
};

enum class Dir {
  North, South, East, West
};

struct Point {
  int x, y;
};

bool operator ==(Point p, Point q) {
  return p.x == q.x && p.y == q.y;
}

struct Pos {
  Point loc;
  Dir dir;
};

Pos exec(In in, Pos pos) {
  switch (in) {
  case In::Forward:
    switch (pos.dir) {
    case Dir::North: return { { pos.loc.x, pos.loc.y + 1 }, pos.dir };
    case Dir::East:  return { { pos.loc.x + 1, pos.loc.y }, pos.dir };
    case Dir::South: return { { pos.loc.x, pos.loc.y - 1 }, pos.dir };
    case Dir::West:  return { { pos.loc.x - 1, pos.loc.y }, pos.dir };
    }
  case In::Left:
    switch (pos.dir) {
    case Dir::North: return { pos.loc, Dir::West };
    case Dir::East:  return { pos.loc, Dir::North };
    case Dir::South: return { pos.loc, Dir::East };
    case Dir::West:  return { pos.loc, Dir::South };
    }
  case In::Right:
    switch (pos.dir) {
    case Dir::North: return { pos.loc, Dir::East };
    case Dir::East:  return { pos.loc, Dir::South };
    case Dir::South: return { pos.loc, Dir::West };
    case Dir::West:  return { pos.loc, Dir::North };
    }
  }
  throw std::runtime_error("Bad exec");
}

vector<In> instructions;
Point finish;

Point execAll() {
  Pos pos = { { 0, 0 }, Dir::North};
  for (auto& in : instructions) {
    pos = exec(in, pos);
  }
  return pos.loc;
}

tuple<int, In> fix() {

  for (int i = 0; i < instructions.size(); ++i) {
    for (In in : { In::Forward, In::Left, In::Right }) {
      if (instructions[i] != in) {
        auto bak = instructions[i];
        instructions[i] = in;
        if (execAll() == finish) {
          return { i + 1, in };
        }
        instructions[i] = bak;
      }
    }
  }

  throw std::runtime_error("no solution");
}

int main() {
  int n;
  cin >> finish.x >> finish.y >> n;
  instructions.resize(n);
  for (auto& in : instructions) {
    string txt;
    cin >> txt;
    if (txt == "Left") in = In::Left;
    else if (txt == "Right") in = In::Right;
    else in = In::Forward;
  }

  auto [i, in] = fix();

  cout << i;
  if (in == In::Left) cout << " Left\n";
  else if (in == In::Right) cout << " Right\n";
  else cout << " Forward\n";
}