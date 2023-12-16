#include <bits/stdc++.h>
using namespace std;

/**
 * Structure calculating bridges, articulation points and biconnected components
 * partition in O(|V| + |E|) time on creation. Assumes vertices are numbered
 * from [1, n] and edges are numbered [1, m].
 */
class GraphConnectivity {
  stack<int> S;
  vector<bool> visited;
  int t;
  int next_bcid;

  void dfs(int v, int parent_edge) {
    visited[v] = true;
    preorder[v] = low[v] = ++t;
    p_edge_id[v] = parent_edge;

    int cnt_children = 0;
    for (auto &[u, id] : adj[v]) {
      if (!visited[u]) {
        cnt_children++;
        S.push(id);
        dfs(u, id);
        low[v] = min(low[v], low[u]);
        if (low[u] >= preorder[v]) {
          art[v] = true;
          while (!S.empty()) {
            int eid = S.top();
            S.pop();
            bcid[eid] = next_bcid;
            if (eid == id)
              break;
          }
          next_bcid++;
        }
      } else if (id != parent_edge) {
        low[v] = min(low[v], preorder[u]);
        if (preorder[u] < preorder[v])
          S.push(id);
      }
    }

    if (v == 1)
      art[v] = (cnt_children >= 2);

    if (parent_edge != -1 && low[v] == preorder[v])
      bridge[parent_edge] = true;
  }

public:
  int n, m;
  vector<list<pair<int, int>>> adj; // adjacency list as pairs {vertex, edge_id}
  vector<int> p_edge_id;            // id of edge to parent in dfs tree
  vector<bool> bridge;              // true iff edge is a bridge
  vector<bool> art;                 // true iff vertex is an articulation point
  vector<int> bcid;                 // biconnected component id of edge
  vector<int> preorder;             // preorder in dfs tree
  vector<int> low;                  // classic low function

  GraphConnectivity(vector<list<pair<int, int>>> _adj) : adj(_adj) {
    n = adj.size() - 1;
    m = 0;
    for (auto &l : adj)
      m += l.size();
    m /= 2;

    bridge.assign(m + 1, false);
    art.assign(n + 1, false);
    bcid.assign(m + 1, 0);
    p_edge_id.assign(n + 1, 0);

    visited.assign(n + 1, false);
    low.assign(n + 1, n + 1);
    preorder.assign(n + 1, 0);

    t = 0;
    next_bcid = 1;

    dfs(1, -1);
  }

  /* Returns articulation points in increasing preorder. */
  vector<int> getArticulationPoints() {
    vector<int> preorder_inv(n + 1, 0);
    for (int v = 1; v <= n; v++)
      preorder_inv[preorder[v]] = v;
    vector<int> articulation_points;
    for (int i = 1; i <= n; i++)
      if (art[preorder_inv[i]])
        articulation_points.push_back(preorder_inv[i]);
    return articulation_points;
  }
};
