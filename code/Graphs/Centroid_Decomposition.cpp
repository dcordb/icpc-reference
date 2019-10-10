//Centroid decomposition basico
//Un centroid es un nodo q al borrarlo divide al arbol en arboles con cnt de nodos <= q la mitad del tamanno del arbol grande

const int MAX = 1e5 + 5;
int n, cent[MAX], sz[MAX];
vector <int> g[MAX];

void dfs2(int u, int pt = 0) {
	sz[u] = 0;

	for(int v : g[u]) {
		if(v == pt || cent[v])
			continue;

		dfs2(v, u);
		sz[u] += sz[v];
	}

	sz[u]++;
}

int dfs1(int u, int r, int pt = 0) {
	int t = -1;

	for(int v : g[u]) {
		if(v == pt || cent[v]) //ojo importante siempre chequear q no vayas a un centroid
			continue;

		if(t == -1 || sz[v] > sz[t])
			t = v;
	}

	if(t == -1 || 2 * sz[t] <= sz[r])
		return u;

	return dfs1(t, r, u);
}

void cdec(int u, int p = 0) { //llamar con cdec(1)
	dfs2(u); //dfs para calcular tamanno de arboles
	int c = dfs1(u, u); //dfs para buscar centroid en el arbol actual

	//hacer lo q haga falta, dfs para calcular cosas, guardar arbol de centroid, etc

	cent[c] = 1; //marco como centroid
	
	for(int v : g[c])
		if(!cent[v])
			cdec(v, c); //seguir con la descomposicion
}