//Articulations points and bridges
//funciona con multi-aristas

const int MAX = 1e5 + 5;
int n, m, t, td[MAX], low[MAX], ed[MAX]; //OJO td y low son hasta cant de nodos, ed es hasta cant de aristas
vector <pair <int, int> > g[MAX];

void dfs(int u) {
	td[u] = low[u] = ++t;

	for(auto o : g[u]) {
		int v = o.first;
		int id = o.second;

		if(!low[v]) {
			ed[id] = 1;
			dfs(v);

			low[u] = min(low[u], low[v]);

			if(low[v] > td[u]) {
				//arista u - v es un bridge
			}

			if((td[u] == 1 && td[v] > 2) || (td[u] != 1 && low[v] >= td[u])) {
				//nodo u es un punto de articulacion
				//OJO puede ser q se detecte varias veces dentro de este ciclo q u es AP
			}
		}

		else if(!ed[id])
			low[u] = min(low[u], td[v]);
	}
}