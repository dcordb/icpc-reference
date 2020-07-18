int exp(int a, int n) {
	int ans = 1;

	while(n > 0) {
		if(n % 2)
			ans = 1LL * ans * a % MOD;
			
		a = 1LL * a * a % MOD;
		n /= 2;
	}
	
	return ans;
}