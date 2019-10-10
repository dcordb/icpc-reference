const int MAX = 2e5 + 5; //poner esto el doble del tamanno necesario

int n;
char a[MAX]; //input string
int lg[MAX], rmq[MAX][20];

int lcp[MAX], lcp_[MAX], last[MAX], sa[MAX], tsa[MAX], ra[MAX], tra[MAX];
int f[MAX];

void csort(int k) { //counting sort
	int m = max(300, n);
	
	for(int i = 0; i <= m; i++)
		f[i] = 0;
	
	for(int i = 1; i <= n; i++)
		f[i + k > n ? 0 : ra[i + k]]++;
		
	for(int i = 0, s = 0; i <= m; i++) {
		int tmp = f[i];
		f[i] = s + 1;
		s += tmp;
	}
	
	for(int i = 1; i <= n; i++) {
		int v = sa[i] + k > n ? 0 : ra[sa[i] + k];
		tsa[f[v]] = sa[i];
		f[v]++;
	}
	
	for(int i = 1; i <= n; i++)
		sa[i] = tsa[i];
}

void build_sa() { //build suffix array
	for(int i = 1; i <= n; i++) {
		sa[i] = i;
		ra[i] = a[i];
	}
	
	for(int k = 1; k <= n; k <<= 1) {
		csort(k);
		csort(0);
		
		int r = 0;
		tra[sa[1]] = ++r;
		
		for(int i = 2; i <= n; i++)
			tra[sa[i]] = (ra[sa[i]] == ra[sa[i - 1]] && ra[sa[i] + k] == ra[sa[i - 1] + k]) ? r : ++r;
			
		for(int i = 1; i <= n; i++)
			ra[i] = tra[i];
			
		if(ra[sa[n]] == n)
			break;
	}
}

void build_lcp() { //build lcp
	last[1] = 0;
	
	for(int i = 2; i <= n; i++)
		last[sa[i]] = sa[i - 1];
		
	for(int i = 1, l = 0; i <= n; i++) {
		if(last[i] == 0) {
			lcp_[i] = 0;
			continue;
		}
		
		while(a[i + l] == a[last[i] + l])
			l++;
			
		lcp_[i] = l;
		l = max(l - 1, 0);
	}
	
	for(int i = 1; i <= n; i++)
		lcp[i] = lcp_[sa[i]];
}

////////////////////////////////////////////////////////////////////////

void build_rmq() { //build rmq for lcp
	for(int i = 1; i <= n; i++) {
		lg[i] = log2(i);
		rmq[i][0] = lcp[i];
	}

	for(int j = 1; (1 << j) <= n; j++) {
		for(int i = 1; i <= n; i++) {
			int pos = i + (1 << (j - 1));
			rmq[i][j] = rmq[i][j - 1];
			
			if(pos <= n)
				rmq[i][j] = min(rmq[i][j], rmq[pos][j - 1]);
		}
	}
}

int query(int a, int b) { //get lcp from a to b
	a++;
	int k = log2(b - a + 1);
	return min(rmq[a][k], rmq[b - (1 << k) + 1][k]);
}
