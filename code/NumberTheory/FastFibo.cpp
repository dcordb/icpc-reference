/*
calculates fib(n) = fib(n - 1) + fib(n - 2) in O(log n)
base cases: fib(0) = fib(1) = 1
*/

map <int, int64> mp;

int64 fib(int n) {
	if(n < 0) return 0;
	if(n < 2) return 1;

	if(mp.count(n))
		return mp[n];

	return mp[n] = (fib((n + 1) / 2) * fib(n / 2) % MOD + fib((n - 1) / 2) * fib((n - 2) / 2) % MOD) % MOD;
}