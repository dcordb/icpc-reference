/*
Lowest Common Ancestor Structure
1-indexed everywhere
*/

struct LCA {
	vector <int> lg, l;
	vector <vector <int> > p, g;

	LCA(vector <vector <int> > g_) {
		g = g_;

		int n = g.size() - 1;

		l.assign(n + 1, 0);
		lg.assign(n + 1, 0);

		for(int i = 1; i <= n; i++)
			lg[i] = log2(i);

		p.assign(n + 1, vector <int> (lg[n] + 1, -1));

		dfs_lca(1);

		for(int j = 1; (1 << j) <= n; j++)
			for(int i = 1; i <= n; i++)
				if(p[i][j - 1] != -1)
					p[i][j] = p[p[i][j - 1]][j - 1];
	}

	void dfs_lca(int u, int lev = 1, int pt = -1) {
		l[u] = lev;
		p[u][0] = pt;

		for(int v : g[u])
			if(v != pt)
				dfs_lca(v, lev + 1, u);
	}

	int lca(int a, int b) {
		if(l[a] < l[b])
			swap(a, b);

		for(int i = lg[l[a]]; i >= 0; i--)
			if(l[a] - (1 << i) >= l[b])
				a = p[a][i];

		if(a == b)
			return a;

		for(int i = lg[l[a]]; i >= 0; i--)
			if(p[a][i] != -1 && p[a][i] != p[b][i])
				a = p[a][i], b = p[b][i];

		return p[a][0];
	}

	int dist(int a, int b) { return l[a] + l[b] - 2 * l[lca(a, b)]; }
};
