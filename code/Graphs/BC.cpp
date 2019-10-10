//Biconnected components
//maneja multiples aristas tambien

const int MAX = 1e6 + 5;
int n, m, sz, t, td[MAX], low[MAX], mk[MAX], ed[MAX]; //OJO a la hora de limpiar los arreglos td y low son de nodos, sin embargo mk y ed son de aristas
vector <pair <int, int> > g[MAX]; //nodo, id
stack <pair <int, int> > s; //stack de edges
vector <pair <int, int> > comp[MAX]; //componentes biconexas, OJO los bridges tambien son componentes biconexas

void dfs(int u) { //antes de llamar dfs limpiar t con t = 0
	td[u] = low[u] = ++t;

	for(auto o : g[u]) {
		int v = o.first;
		int id = o.second;

		if(!mk[id]) {
			mk[id] = 1;
			s.push({u, v});
		}

		if(!low[v]) {
			ed[id] = 1;
			dfs(v);

			low[u] = min(low[u], low[v]);

			if(low[v] >= td[u]) {
				sz++;

				while(1) {
					auto w = s.top();
					s.pop();
					comp[sz].push_back(w);

					if(w == make_pair(u, v))
						break;
				}
			}
		}

		else if(!ed[id])
			low[u] = min(low[u], td[v]);
	}
}