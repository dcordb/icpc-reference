const int MAX = 4e5 + 5; //poner esto el doble del tamanno necesario
int n; //size of input string
int lcp[MAX], lcp_[MAX], last[MAX], sa[MAX], tsa[MAX], ra[MAX], tra[MAX];
int f[MAX];
char a[MAX]; //input string

void csort(int k) {
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

void build_sa() {
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

void build_lcp() {
	last[1] = 0;
	
	for(int i = 2; i <= n; i++)
		last[sa[i]] = sa[i - 1];
		
	for(int i = 1, l = 0; i <= n; i++) {
		if(last[i] == 0) {
			lcp_[i] = 0;
			continue;
		}
		
		//look here
		while(a[i + l] != '$' && a[last[i] + l] != '$' && a[i + l] == a[last[i] + l])
			l++;
			
		lcp_[i] = l;
		l = max(l - 1, 0);
	}
	
	for(int i = 1; i <= n; i++)
		lcp[i] = lcp_[sa[i]];
}

////////////////////////////////////////////////////////////////////////
int id[MAX];
char w[MAX];

int main() {
	int sz = 1e9;
	for(int i = 1; i <= 3; i++) {
		scanf("%s", w + 1);
		int l = strlen(w + 1);
		sz = min(sz, l);
		w[++l] = '$';
		
		for(int j = 1; j <= l; j++) {
			sa[j + n] = j + n;
			ra[j + n] = w[j];
			a[j + n] = w[j];
		}
		
		for(int j = n + 1; j < n + l; j++)
			id[j] = i;
			
		n += l;
	}
	
	build_sa();
	build_lcp();
	return 0;
}
