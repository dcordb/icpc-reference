namespace HK {
	const int MAX = 640000 + 5; //total of nodes, 1 <= id_nodes <= MAX
	const int INF = 1e9;
	int n, l, r, right[MAX], left[MAX], d[MAX];
	vector <int> g[MAX];

	void init(int l_, int r_) { //nodos de izq enumerados desde 1 a l y der desde l + 1 .. l + r; l + r == n
		l = l_;
		r = r_;
		n = l + r;

		for(int i = 1; i <= n; i++)
			g[i].clear();
	}

	void addEdge(int a, int b) { //left and right
		g[a].push_back(b);
		g[b].push_back(a);
	}

	bool bfs() {
		queue <int> q;
		
		for(int i = 1; i <= n; i++)
			d[i] = INF;

		for(int i = 1; i <= l; i++) {
			if(left[i] == 0) {
				d[i] = 0;
				q.push(i);
			}
		}

		d[0] = INF;

		while(!q.empty()) {
			int u = q.front();
			q.pop();

			if(u == 0)
				continue;

			for(int v : g[u]) {
				if(d[right[v]] == INF) {
					d[right[v]] = d[u] + 1;
					q.push(right[v]);
				}
			}
		}

		return d[0] != INF;
	}

	bool dfs(int u) {
		if(u == 0)
			return true;

		for(int v : g[u]) {
			if(d[right[v]] == d[u] + 1 && dfs(right[v])) {
				right[v] = u;
				left[u] = v;
				return true;
			}
		}

		d[u] = INF;
		return false;
	}

	int matching() {
		int res = 0;

		memset(left, 0, sizeof(left));
		memset(right, 0, sizeof(right));

		while(bfs())
			for(int i = 1; i <= l; i++)
				if(left[i] == 0 && dfs(i))
					res++;

		return res;
	}
}