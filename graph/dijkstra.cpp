#include <cassert>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll;

vector<ll> dijkstra(const vector<vector<pair<int, ll>>> &graph, int s) {
  vector<ll> dist(graph.size(), 1e18);
  priority_queue<pair<ll, int>> q;
  q.push(pair<ll, int>{0, s});
  while (!q.empty()) {
    int i = q.top().second;
    ll di = -q.top().first;
    q.pop();
    if (dist[i] <= di) continue;
    dist[i] = di;
    for (auto e : graph[i]) {
      int j = e.first;
      ll dj = di + e.second;
      if (dist[j] > dj) q.push(pair<ll, int>{-dj, j});
    }
  }
  return dist;
}

int main() {
  vector<vector<pair<int, ll>>> graph(7);
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
  auto dist = dijkstra(graph, 0);
  assert(dist[0] == 0);
  assert(dist[1] == 2);
  assert(dist[2] == 5);
  assert(dist[3] == 7);
  assert(dist[4] == 11);
  assert(dist[5] == 8);
  assert(dist[6] == 16);
}
