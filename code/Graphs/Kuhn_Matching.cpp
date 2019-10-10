namespace kuhn {
	const int MAX = 2e4 + 5; //total de nodos
	int n, l, r, mk[MAX], left[MAX], right[MAX];
	vector <int> g[MAX], e;

	void init(int l_, int r_) { //nodos de izq enumerados desde 1 a l y der desde l + 1 .. l + r; l + r == n
		l = l_;
		r = r_;
		n = l + r;

		for(int i = 1; i <= n; i++)
			g[i].clear();
	}

	void addEdge(int a, int b) { //izq y der
		g[a].push_back(b);
	}

	int dfs(int u) {
		if(mk[u])
			return 0;

		mk[u] = 1;
		e.push_back(u);

		for(int v : g[u]) {
			if(right[v] == 0 || dfs(right[v])) {
				right[v] = u;
				left[u] = v;
				return 1;
			}
		}

		return 0;
	}

	int matching() {
		for(int i = 1; i <= n; i++)
			left[i] = right[i] = 0;

		int ans = 0;
		for(int i = 1; i <= l; i++) {
			e.clear();
			ans += dfs(i);
			
			for(int o : e)
				mk[o] = 0;
		}

		return ans;
	}
}