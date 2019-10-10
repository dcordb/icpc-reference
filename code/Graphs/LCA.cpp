//Lowest Common Ancestor
const int MAX = 1e5 + 5; //cantidad de nodos, nodos enumerados a partir de 1
int l[MAX], lg[MAX], p[MAX][20]; //niveles, logaritmos y tabla de padres de tamanno n * log n

void dfs_lca(int u, int lev = 1, int pt = 0) { //dfs para inicializar lca
	l[u] = lev;
	p[u][0] = pt;

	for(int v : g[u])
		if(v != pt)
			dfs_lca(v, lev + 1, u);
}

void init_lca() { //llamar aqui de primero
	dfs_lca(1);

	for(int i = 1; i <= n; i++)
		lg[i] = log2(i);

	for(int j = 1; (1 << j) <= n; j++)
		for(int i = 1; i <= n; i++)
			p[i][j] = p[p[i][j - 1]][j - 1];
}

int lca(int a, int b) { //funcion que halla lca
	if(l[a] < l[b])
		swap(a, b);

	for(int i = lg[l[a]]; i >= 0; i--)
		if(l[a] - (1 << i) >= l[b])
			a = p[a][i];

	if(a == b)
		return a;

	for(int i = lg[l[a]]; i >= 0; i--)
		if(p[a][i] && p[a][i] != p[b][i])
			a = p[a][i], b = p[b][i];

	return p[a][0];
}