int64 exp(int64 a, int64 n) {
	int64 ans = 1;
	while(n > 0) {
		if(n % 2LL == 1LL)
			ans = ans * a % MOD;
			
		a = a * a % MOD;
		n /= 2LL;
	}
	
	return ans;
}