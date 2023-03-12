#include <bits/stdc++.h>
using namespace std;

const int inf = numeric_limits<int>::max();

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);

    int n, m;
    cin >> n >> m;

    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }

    vector<pair<int, int>> d(n, {inf, -1}), ans;
    vector<int> seen(n);
    int mst = 0;
    d[0] = {0, -1};

    for (int i = 0; i < n; i++) {
        int u = -1;
        for (int k = 0; k < n; k++)
            if (!seen[k] && (u == -1 || d[k] < d[u])) u = k;

        if (d[u].first == inf) break;  // no mst here

        mst += d[u].first;
        seen[u] = 1;

        if (d[u].second != -1) ans.push_back({d[u].second, u});

        for (auto [v, w] : g[u])
            if (w < d[v].first) d[v] = {w, u};
    }

    cout << mst << "\n";
    for (auto [a, b] : ans) cout << a + 1 << " " << b + 1 << "\n";
    return 0;
}
