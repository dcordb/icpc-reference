//matrix multiplication con memoria dinamica, funciona ok

const int MOD = 1e9 + 7;

struct matrix { //matrix empieza de 0
	int n, m;
	int** a; //memoria dinamica

	matrix() {}

	matrix(int n_, int m_) {
		n = n_, m = m_;

		a = new int*[n];

		for(int i = 0; i < n; i++)
			a[i] = new int[m];

		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				a[i][j] = 0;
	}

	matrix operator * (const matrix &t) {
		int p = t.m;
		matrix res(n, p);

		for(int i = 0; i < n; i++) {
			for(int j = 0; j < p; j++) {
				for(int k = 0; k < m; k++) {
					int v = (a[i][k] * 1LL * t.a[k][j]) % MOD;
					res.a[i][j] = (res.a[i][j] + v) % MOD;
				}
			}
		}

		return res;
	}

	void print() {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++)
				printf("%d ", a[i][j]);
			printf("\n");
		}

		printf("\n");
	}
};