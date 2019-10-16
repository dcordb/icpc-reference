namespace sat {
	/*2sat variables are at even positions (0, 2, 4, 6, ...)
	negations are at odd positions (1, 3, 5, 7, ...)*/
	/*
	para annadir variable x, poner 2 * x
	para annadir neg(x) poner neg(2 * x)
	*/

	int n;
	vector <vector <int> > g, gt;
	vector <int> order, mk;

	void init(int N) { //call this first!, parameter is number of variables
		n = N;
		g.clear();
		gt.clear();
		g.resize(2 * n);
		gt.resize(2 * n);
	}

	int neg(int x) {
		return x ^ 1;
	}

	void addOr(int a, int b) {
		g[neg(a)].push_back(b);
		gt[b].push_back(neg(a));

		g[neg(b)].push_back(a);
		gt[a].push_back(neg(b));
	}

	void addXor(int a, int b) {
		addOr(a, b);
		addOr(neg(a), neg(b));
	}

	void addNotXor(int a, int b) {
		addOr(neg(a), b);
		addOr(a, neg(b));
	}

	void addImplication(int a, int b) {
		addOr(neg(a), b);
	}

	void dfs1(int u) {
		mk[u] = 1;

		for(int v : g[u])
			if(!mk[v])
				dfs1(v);

		order.push_back(u);
	}

	void dfs2(int u, vector <int> &nodes) {
		mk[u] = 1;
		nodes.push_back(u);

		for(int v : gt[u])
			if(!mk[v])
				dfs2(v, nodes);
	}

	bool solve(vector <int> &res) {
		mk.assign(2 * n, 0);
		order.clear();

		for(int i = 0; i < 2 * n; i++)
			if(!mk[i])
				dfs1(i);

		reverse(order.begin(), order.end());

		mk.assign(2 * n, 0);

		vector <int> id(2 * n, 0);
		vector <int> nodes;

		int c = 0;
		for(int o : order) {
			if(!mk[o]) {
				nodes.clear();
				dfs2(o, nodes);

				c++;
				for(int o : nodes)
					id[o] = c;
			}
		}

		res.assign(n, 0);
		for(int i = 0; i < 2 * n; i += 2) {
			if(id[i] == id[neg(i)])
				return false;

			res[i / 2] = id[i] > id[neg(i)];
		}

		return true;
	}
}