//Small To Large On Trees O(n * log n * O(estructura))

const int MAX = 1e5 + 5;

int n, t, c[MAX], inv[MAX], sz[MAX], td[MAX], tf[MAX];
vector <int> g[MAX];

int64 sum_freq[MAX], ans[MAX];
int cnt_freq[MAX], freq[MAX];
multiset <int> s;

void dfs_(int u, int p = -1) { //llamar a este dfs primero para inicializar info
	td[u] = ++t;
	inv[t] = u;

	for(int v : g[u]) {
		if(v != p) {
			dfs_(v, u);
			sz[u] += sz[v];
		}
	}

	sz[u]++;
	tf[u] = t;
}

void add(int x) {
	int val = c[inv[x]];

	//esto es del problema especifico,
	//en este caso se lleva la frecuencia maxima,
	//cuantas veces aparece y la suma de los valores con frecuencia maxima

	if(cnt_freq[freq[val]] == 1)
		s.erase(s.find(freq[val]));

	if(cnt_freq[freq[val]] > 0) {
		cnt_freq[freq[val]]--;
		sum_freq[freq[val]] -= val;
	}

	freq[val]++;
	cnt_freq[freq[val]]++;
	sum_freq[freq[val]] += val;

	if(cnt_freq[freq[val]] == 1)
		s.insert(freq[val]);
}

void rem(int x) {
	int val = c[inv[x]];

	//esto es del problema especifico

	if(cnt_freq[freq[val]] == 1)
		s.erase(s.find(freq[val]));

	if(cnt_freq[freq[val]] > 0) {
		cnt_freq[freq[val]]--;
		sum_freq[freq[val]] -= val;
	}

	freq[val]--;
	cnt_freq[freq[val]]++;
	sum_freq[freq[val]] += val;

	if(cnt_freq[freq[val]] == 1)
		s.insert(freq[val]);
}

void dfs(int v, int p = -1, bool keep = 0) {
	int mx = -1, bigChild = -1;
	for(auto u : g[v])
		if(u != p && sz[u] > mx)
			mx = sz[u], bigChild = u;
	
	for(auto u : g[v])
		if(u != p && u != bigChild)
			dfs(u, v, 0);  // run a dfs on small childs and clear them from cnt
	
	if(bigChild != -1)
		dfs(bigChild, v, 1);  // bigChild marked as big and not cleared from cnt
	
	for(auto u : g[v])
		if(u != p && u != bigChild)
			for(int p = td[u]; p <= tf[u]; p++)
				add(p); //annadir a la estructura
	
	add(td[v]);

	//responder las queries
	////////////////////////////////////
	int mFreq = *s.rbegin();
	ans[v] = sum_freq[mFreq];
	////////////////////////////////////

	if(keep == 0)
		for(int p = td[v]; p <= tf[v]; p++)
			rem(p); //quitar de la estructura
}