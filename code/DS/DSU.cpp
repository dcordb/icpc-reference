struct DSU {
	vector <int> p, sz;
	stack <pair <int, int> > s;

	DSU(int n) {
		p.assign(n + 1, 0);
		sz.assign(n + 1, 0);

		for(int i = 1; i <= n; i++)
			p[i] = i, sz[i] = 1;
	}

	int findst(int x) { return (x == p[x]) ? x : findst(p[x]); } //without path compression

	void joinst(int a, int b) { //representativo de cada set
		if(sz[a] < sz[b])
			swap(a, b);

		sz[a] += sz[b];
		p[b] = a;

		s.push({ a, b });
	}

	void rollback() {
		assert(!s.empty());

		int a = s.top().first;
		int b = s.top().second;
		s.pop();

		sz[a] -= sz[b];
		p[b] = b;
	}
};