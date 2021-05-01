#include <cassert>
#include <limits>
#include <queue>
#include <vector>

template <class T>
std::vector<T> Dijkstra(const std::vector<std::vector<std::pair<int, T>>>& graph, int s) {
  std::vector<T> dist(graph.size(), std::numeric_limits<T>::max());
  std::priority_queue<std::pair<T, int>> q;
  dist[s] = 0;
  q.emplace(0, s);
  while (!q.empty()) {
    int i = q.top().second;
    T di = -q.top().first;
    q.pop();
    if (dist[i] < di) continue;
    for (auto e : graph[i]) {
      int j = e.first;
      T dj = di + e.second;
      if (dist[j] <= dj) continue;
      dist[j] = dj;
      q.emplace(-dj, j);
    }
  }
  return dist;
}

// test
int main() {
  std::vector<std::vector<std::pair<int, long long>>> graph(7);
  auto add_undirected_edge = [&graph](int a, int b, int cost) {
    graph[a].push_back({b, cost});
    graph[b].push_back({a, cost});
  };
  add_undirected_edge(0, 1, 2);
  add_undirected_edge(0, 2, 5);
  add_undirected_edge(1, 2, 4);
  add_undirected_edge(1, 3, 6);
  add_undirected_edge(1, 4, 10);
  add_undirected_edge(2, 3, 2);
  add_undirected_edge(3, 5, 1);
  add_undirected_edge(4, 5, 3);
  add_undirected_edge(4, 6, 5);
  add_undirected_edge(5, 6, 9);
  auto dist = Dijkstra(graph, 0);
  assert(dist[0] == 0);
  assert(dist[1] == 2);
  assert(dist[2] == 5);
  assert(dist[3] == 7);
  assert(dist[4] == 11);
  assert(dist[5] == 8);
  assert(dist[6] == 16);
}
