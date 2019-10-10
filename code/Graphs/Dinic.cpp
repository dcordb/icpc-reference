namespace Dinic {
	typedef int T; //change to long long if needed

	struct edge {
		int from, to;
		T f; //faltan f unidades de flujo por pasar, han pasado capacidad - f
	};

	const int MAX = 2e4 + 5; //cantidad de nodos
	const T INF = 1e9; //if T is long long change to 1e18

	int n, s, t, pt[MAX], d[MAX];
	vector <edge> e;
	vector <int> g[MAX];
	queue <int> q;

	void init(int n_, int s_, int t_) { //nodes, source and sink 1 <= s, t <= n, nodos enumerados de 1 a n
		n = n_, s = s_, t = t_;

		for(int i = 1; i <= n; i++)
			g[i].clear();
		e.clear();
	}

	void addEdge(int from, int to, T c) {
		edge ed;
		ed.from = from, ed.to = to, ed.f = c;
		e.push_back(ed);
		g[from].push_back((int) e.size() - 1);

		ed.from = to, ed.to = from, ed.f = 0;
		e.push_back(ed);
		g[to].push_back((int) e.size() - 1);
	}

	bool bfs() {
		for(int i = 1; i <= n; i++)
			d[i] = -1;

		d[s] = 0;
		q.push(s);

		while(!q.empty()) {
			int u = q.front();
			q.pop();

			for(int id : g[u]) {
				int v = e[id].to;

				if(d[v] == -1 && e[id].f > 0) {
					d[v] = d[u] + 1;
					q.push(v);
				}
			}
		}

		return d[t] != -1;
	}

	T dfs(int u, T flow = INF) {
		if(u == t)
			return flow;

		for(; pt[u] < (int) g[u].size(); pt[u]++) {
			int id = g[u][pt[u]];
			int v = e[id].to;

			if(d[u] + 1 != d[v] || e[id].f == 0)
				continue;

			T pushed = dfs(v, min(flow, e[id].f));

			if(pushed > 0) {
				e[id].f -= pushed;
				e[id ^ 1].f += pushed;
				return pushed;
			}
		}

		return 0;
	}

	T getMaxFlow() {
		T ans = 0;

		while(1) {
			if(!bfs())
				break;

			for(int i = 1; i <= n; i++)
				pt[i] = 0;

			T f;
			while((f = dfs(s)))
				ans += f;
		}

		return ans;
	}
}