const int MOD = 998244353;
typedef vector <vector <int> > matrix;

matrix operator * (const matrix &a, const matrix &b) {
	assert(a[0].size() == b.size());

	int n = a.size();
	int m = b.size();
	int p = b[0].size();

	matrix c(n, vector <int> (p));

	for(int i = 0; i < n; i++)
		for(int j = 0; j < p; j++)
			for(int k = 0; k < m; k++)
				c[i][j] = (c[i][j] + 1LL * a[i][k] * b[k][j] % MOD) % MOD;

	return c;
}

matrix I(int n) {
	matrix a(n, vector <int> (n));

	for(int i = 0; i < n; i++)
		a[i][i] = 1;

	return a;
}

matrix exp(matrix a, int64 n) {
	matrix ans = I(a.size());

	while(n > 0) {
		if(n % 2LL == 1LL)
			ans = ans * a;
			
		a = a * a;
		n /= 2LL;
	}
	
	return ans;
}