//Succesive Shortest Paths
//works if graph has negative cycles
//si el grafo no tiene ciclos negativos no hace falta la parte del bellman ford

typedef long long int64;
typedef pair <int64, int> par; //costo y flujo

namespace MCF {
	const int MAX = 1e4 + 5;
	const int64 INF = (int64) 1e18;

	struct edge {
		int from, to, flow, cap;
		int64 cost;
	};

	vector <edge> e;
	vector <int> g[MAX];
	int64 phi[MAX], dist[MAX];
	priority_queue <par> q;
	int n, s, t, p[MAX];

	void init(int n_, int s_, int t_) { //OJO nodos enumerados desde cero 0 <= nodo, s, t < n
		n = n_, s = s_, t = t_;

		for(int i = 0; i < n; i++) {
			g[i].clear();
			p[i] = 0;
		}

		e.clear();
	}

	void addEdge(int from, int to, int cap, int64 cost) {
		edge ed;
		ed.from = from, ed.to = to, ed.flow = 0, ed.cap = cap, ed.cost = cost;
		g[from].push_back((int) e.size());
		e.push_back(ed);

		ed.from = to, ed.to = from, ed.flow = cap, ed.cap = cap, ed.cost = -cost;
		g[to].push_back((int) e.size());
		e.push_back(ed);
	}

	void bellmanFord() {
		for(int i = 0; i < n; i++)
			dist[i] = INF;

		dist[s] = 0;

		while(1) {
			int change = 0;

			for(auto o : e) {
				int from = o.from;
				int to = o.to;

				if(o.flow == o.cap || dist[from] == INF)
					continue;

				if(dist[from] + o.cost < dist[to]) {
					dist[to] = dist[from] + o.cost;
					change = 1;
				}
			}

			if(!change)
				break;
		}
	}

	void dijkstra() {
		while(!q.empty())
			q.pop();

		for(int i = 0; i < n; i++) {
			dist[i] = INF;
			q.push({-dist[i], i});
		}

		dist[s] = 0;
		q.push({0, s});

		while(!q.empty()) {
			int u = q.top().second;
			int64 ct = -q.top().first;
			q.pop();

			if(ct > dist[u])
				continue;

			if(dist[u] == INF)
				break;

			for(int id : g[u]) {
				if(e[id].flow == e[id].cap)
					continue;

				int to = e[id].to;
				int64 w = e[id].cost + phi[u] - phi[to];

				if(ct + w < dist[to]) {
					dist[to] = ct + w;
					p[to] = id;
					q.push({-dist[to], to});
				}
			}
		}
	}

	par maxFlowMinCost() {
		int64 flowCost = 0;
		int flow = 0;

		bellmanFord();

		for(int i = 0; i < n; i++)
			phi[i] = dist[i];

		while(1) {
			dijkstra();

			if(dist[t] == INF)
				break;

			for(int i = 0; i < n; i++)
				phi[i] = min(phi[i] + dist[i], INF);

			int push = (int) 1e9;
			int u = t;

			while(u != s) {
				edge tmp = e[p[u]];
				push = min(push, tmp.cap - tmp.flow);
				u = tmp.from;
			}

			flow += push;
			u = t;

			while(u != s) {
				edge tmp = e[p[u]];
				e[p[u]].flow += push;
				e[p[u] ^ 1].flow -= push;
				flowCost += 1LL * push * tmp.cost;
				u = tmp.from;
			}
		}

		return {flowCost, flow};
	}
}