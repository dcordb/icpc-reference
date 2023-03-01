/*
BiConnectivity Algorithms:
    - finds articulation points
    - finds bridges
    - finds biconnected components (note, a bridge is also a biconnected
component and the algorithm finds them too)

    An articulation point is a node such that when removed disconnects the
graph. A bridge is an edge such that when removed disconnects the graph. A
biconnected component is a maximal connected component such that between any two
nodes there exist at least 2 disjoint edge paths.

    Time Complexity: O(n + m)
*/

struct BiConnectivity {
    vector<vector<pair<int, int>>> g;
    vector<int> td, low;
    vector<bool> mk, ed, br, ap;

    vector<vector<pair<int, int>>> comp;
    stack<pair<int, int>> s;

    int t = 0;

    // the graph is an adjacency list of pairs (node, id of edge)
    BiConnectivity(const vector<vector<pair<int, int>>> &g) : g(g) {
        int n = g.size();
        int m = 0;

        for (int i = 0; i < n; i++) m += g[i].size();

        m /= 2;

        td.assign(n, -1);
        low.assign(n, -1);
        ap.assign(n, false);  // is articulation point ?

        mk.assign(m, false);
        ed.assign(m, false);
        br.assign(m, false);  // is bridge ?

        for (int i = 0; i < n; i++)
            if (low[i] == -1) dfs(i, 1);
    }

    function<void(int, int)> dfs = [&](int u, int r) {
        td[u] = low[u] = ++t;

        for (auto o : g[u]) {
            int v = o.first;
            int id = o.second;

            if (!mk[id]) {
                mk[id] = true;
                s.push({u, v});
            }

            if (low[v] == -1) {
                ed[id] = true;
                dfs(v, 0);

                low[u] = min(low[u], low[v]);

                if (low[v] > td[u]) br[id] = true;  // found a bridge

                if ((r && td[v] - td[u] > 1) || (!r && low[v] >= td[u]))
                    ap[u] = true;  // found an articulation point

                if (low[v] >= td[u]) {  // found a biconnected component
                    comp.push_back({});

                    while (1) {
                        auto w = s.top();
                        s.pop();
                        comp.back().push_back(w);

                        if (w == make_pair(u, v)) break;
                    }
                }
            }

            else if (!ed[id])
                low[u] = min(low[u], td[v]);
        }
    };
};

/*
Usage:
    g is an adjacency list of pairs (node, id), for example:

    vector <vector <pair <int, int>>> g(n);
    for(int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }

    NOTE: nodes and edges are supposed to be 0-indexed.

    BiConnectivity bi(g);

Tested On:
    https://codeforces.com/gym/102835/problem/I
    https://judge.yosupo.jp/problem/two_edge_connected_components
*/
