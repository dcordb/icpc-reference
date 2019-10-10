//HLD, mantener un segtree de 1 a n con la informacion de cada nodo
//inv[st] es que nodo ocupa la posicion st en segtree
//idea: HLD descompone el arbol en cadenas
//arista heavy: es la que va al subarbol mas pesado, es light en otro caso
//la cantidad de aristas light desde la raiz a 1 hoja es O(log n)

//arreglos, MAX es cantidad de nodos maxima
int n, q, ch, st, inv[MAX], l[MAX], chain[MAX], pt[MAX], sz[MAX], head[MAX], posChain[MAX];
vector <int> g[MAX];

void dfs1(int u, int p = -1, int lev = 1) {
	l[u] = lev;

	for(int v : g[u]) {
		if(v == p)
			continue;

		dfs1(v, u, lev + 1);

		pt[v] = u;
		sz[u] += sz[v];
	}

	sz[u]++;
}

void dfs2(int u, int p = -1, int light = 1) {
	if(light) { //if edge from p to u is light, a new chain start
		ch++; //number of chains
		head[ch] = u; //head of chain
	}

	//a chain continues
	chain[u] = ch; //in which chain is u?
	posChain[u] = ++st; //pos of u in segment tree
	inv[st] = u; //who is in pos st in seg tree, inv of poschain

	int t = -1;

	for(int v : g[u]) {
		if(v == p)
			continue;

		if(t == -1 || sz[v] > sz[t])
			t = v;
	}

	if(t != -1)
		dfs2(t, u, 0); //now the edge is heavy

	for(int v : g[u]) {
		if(v == p || v == t)
			continue;

		dfs2(v, u, 1); //edge is light
	}
}

int lca(int a, int b) { //NO hace falta para la implementacion de query y update, lo tengo por si acaso
	while(chain[a] != chain[b]) {
		int x = chain[a];
		int y = chain[b];

		if(l[head[x]] > l[head[y]])
			a = pt[head[x]];

		else b = pt[head[y]];
	}

	return l[a] < l[b] ? a : b;
}

int query(int a, int b) { //no hay casos bordes
	int res = 0;

	while(chain[a] != chain[b]) {
		int x = chain[a];
		int y = chain[b];

		if(l[head[y]] > l[head[x]]) {
			swap(a, b); //a es mas profundo
			swap(x, y);
		}

		res = merge(res, query(1, 1, n, posChain[head[x]], posChain[a]));
		a = pt[head[x]];
	}

	if(l[b] > l[a])
		swap(a, b);

	//para usar con aristas cambiar posChain[b] por posChain[b] + 1
	res = merge(res, query(1, 1, n, posChain[b], posChain[a])); //a es mas profundo
	return res;
}

void update(int a, int b, int v) { //no hay casos bordes
	while(chain[a] != chain[b]) {
		int x = chain[a];
		int y = chain[b];

		if(l[head[y]] > l[head[x]]) {
			swap(a, b); //a es mas profundo
			swap(x, y);
		}

		upd(1, 1, n, posChain[head[x]], posChain[a], v);
		a = pt[head[x]];
	}

	if(l[b] > l[a])
		swap(a, b);

	//para usar con aristas cambiar posChain[b] por posChain[b] + 1
	upd(1, 1, n, posChain[b], posChain[a], v); //a es mas profundo;
}