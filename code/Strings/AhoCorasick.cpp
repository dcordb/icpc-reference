const int
	MAXN = 1e4 + 1,
	MAXM = 1e6 + 1,
	MAXK = 1e3 + 1;
int n, sz, e, f[MAXM], dp[MAXN], t[MAXN], seen[MAXN], tam[MAXN], trie[MAXM][26];
vector <int> ac[MAXM], g[MAXN];
char s[MAXN][MAXK];
queue <int> q;

void clean() {
	sz = 0;
	for(int i = 0; i < MAXM; i++) {
		for(int j = 0; j < 26; j++)
			trie[i][j] = -1;

		f[i] = 0;
		ac[i].clear();
	}

	for(int i = 1; i <= n; i++) {
		tam[i] = seen[i] = t[i] = dp[i] = 0;
		g[i].clear();
	}
}

void read() {
	for(int i = 1; i <= n; i++) {
		scanf("%s", s[i] + 1);

		int l = strlen(s[i] + 1), k = 0;
		tam[i] = l;
		for(int j = 1; j <= l; j++) {
			int c = s[i][j] - 'a';

			if(trie[k][c] == -1)
				trie[k][c] = ++sz;
			k = trie[k][c];
		}

		ac[k].push_back(i);
	}
}

void buildAC() {
	for(int i = 0; i < 26; i++) {
		if(trie[0][i] != -1)
			q.push(trie[0][i]);

		else trie[0][i] = 0;
	}

	while(!q.empty()) {
		int u = q.front();
		q.pop();

		for(int i = 0; i < 26; i++) {
			if(trie[u][i] == -1)
				continue;

			int k = f[u];

			while(k > 0 && trie[k][i] == -1)
				k = f[k];

			k = trie[k][i];
			f[trie[u][i]] = k;

			for(int j = 0; j < (int) ac[k].size(); j++)
				ac[trie[u][i]].push_back(ac[k][j]);

			q.push(trie[u][i]);
		}
	}
}

void dfs(int u) {
	seen[u] = 1;

	for(int i = 0; i < (int) g[u].size(); i++) {
		int v = g[u][i];

		if(!seen[v])
			dfs(v);
	}

	t[++e] = u;
}

void solve() {
	for(int i = 1; i <= n; i++) {
		int l = tam[i], k = 0;

		for(int j = 1; j <= l; j++) {
			int c = s[i][j] - 'a';

			while(k > 0 && trie[k][c] == -1)
				k = f[k];

			k = trie[k][c];

			for(int l = 0; l < (int) ac[k].size(); l++) {
				int id = ac[k][l];

				if(tam[i] > tam[id])
					g[id].push_back(i);
			}
		}
	}

	//esto es del problema en cuestion

	e = 0;
	for(int i = 1; i <= n; i++)
		if(!seen[i])
			dfs(i);

	for(int i = n; i > 0; i--) {
		int u = t[i];

		for(int j = 0; j < (int) g[u].size(); j++) {
			int v = g[u][j];
			dp[v] = max(dp[v], dp[u] + 1);
		}
	}

	printf("%d\n", *max_element(dp + 1, dp + n + 1) + 1);
}

int main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	while(1) {
		scanf("%d", &n);

		if(n == 0)
			break;

		clean();
		read();
		buildAC();
		solve();
	}

	return 0;
}
