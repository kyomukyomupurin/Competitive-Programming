// Bellman Ford algorithm
// verified by
//     https://onlinejudge.u-aizu.ac.jp/courses_/library/5/GRL/1/GRL_1_B

#include <cassert>
#include <limits>
#include <vector>

#include "./graph.cc"

// snippet-begin
template <class T>
std::vector<T> bellmanford(const graph<T>& g, int s) {
  assert(0 <= s && s < g.n_);
  constexpr T kInfinity = std::numeric_limits<T>::max();
  std::vector<T> dist(g.n_, kInfinity);
  dist[s] = 0;
  for (int i = 0; i < g.n_; ++i) {
    for (const auto& [from, to, cost] : g.edges_) {
      if (dist[from] == kInfinity) continue;
      if (dist[to] > dist[from] + cost) {
        dist[to] = dist[from] + cost;
      }
    }
  }
  for (const auto& [from, to, cost] : g.edges_) {
    if (dist[from] == kInfinity) continue;
    if (dist[to] > dist[from] + cost) return {};
  }
  return dist;
}
// snippet-end

// verification code
/*
void GRL_1_B() {
  int n, m, r; cin >> n >> m >> r;
  digraph<int> g(n);
  for (int i = 0; i < m; ++i) {
    int s, t, d; cin >> s >> t >> d;
    g.add(s, t, d);
  }

  constexpr int kInfinity = numeric_limits<int>::max();

  vector<int> dist = bellmanford(g, r);
  if (dist.empty()) {
    cout << "NEGATIVE CYCLE" << '\n';
  } else {
    for (int e : dist) {
      if (e == kInfinity) {
        cout << "INF" << '\n';
      } else {
        cout << e << '\n';
      }
    }
  }
}
*/