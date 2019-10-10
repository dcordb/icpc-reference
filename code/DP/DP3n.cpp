for(int mask = 1; mask < l; mask++) { //O(3 ^ N)
	for(int msk = mask; msk > 0; msk = (msk - 1) & mask) { //msk iterates every subset of mask
		int ct = dp[mask ^ msk] + p[msk];
			
		if(ct < dp[mask])
			dp[mask] = ct;
	}
}