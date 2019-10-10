struct permutation {
	int n;
	vector <int> a;

	permutation(int n_) {
		n = n_;
		a.assign(n + 1, 0);

		for(int i = 1; i <= n; i++)
			a[i] = i;
	}

	permutation comp(const permutation &t) const { //*this comp t
		permutation res(n);
		for(int i = 1; i <= n; i++)
			res.a[i] = a[t.a[i]];

		return res;
	}

	permutation inv() const { //inverse of *this
		permutation res(n);
		for(int i = 1; i <= n; i++)
			res.a[a[i]] = i;

		return res;
	}

	void print() {
		for(int i = 1; i <= n; i++) {
			printf("%d", a[i]);
			printf(i == n ? "\n" : " ");
		}
	}
};