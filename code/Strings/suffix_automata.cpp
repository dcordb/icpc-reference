//solution of http://codeforces.com/contest/128/problem/B
//find kth lexicographical substring (counting also equals substring)

#include <bits/stdc++.h>
using namespace std;

typedef long long int64;
const int MAX = 1e5 + 5;

int sz, last;
 
struct state {
	int len, link;
	bool cloned;
	map <char, int> nxt;
} st[2 * MAX];
 
void sa_init(int n) {
	for(int i = 0; i <= 2 * n; i++) {
		st[i].len = st[i].link = 0;
		st[i].cloned = false;
		st[i].nxt.clear();
	}

	sz = last = 0;
	st[0].len = 0;
	st[0].link = -1;
	sz++;
}
 
void sa_extend(char c) {
	int cur = sz++;
	st[cur].len = st[last].len + 1;
	
	int p = last;
	for(; p != -1 && !st[p].nxt.count(c); p = st[p].link)
		st[p].nxt[c] = cur;
		
	if(p == -1)
		st[cur].link = 0;
		
	else {
		int q = st[p].nxt[c];
		
		if(st[p].len + 1 == st[q].len)
			st[cur].link = q;
			
		else {
			int clone = sz++;
			st[clone].len = st[p].len + 1;
			st[clone].nxt = st[q].nxt;
			st[clone].link = st[q].link;
			st[clone].cloned = true;
			
			for(; p != -1 && st[p].nxt[c] == q; p = st[p].link)
				st[p].nxt[c] = clone;
				
			st[q].link = st[cur].link = clone;
		}
	}
	
	last = cur;
}

int n, k, l, cnt[2 * MAX], ord[2 * MAX], term[2 * MAX], mk[2 * MAX];
int64 dp[2 * MAX];
char a[MAX];

void dfs(int u) {
	mk[u] = 1;

	for(auto o : st[u].nxt) {
		int v = o.second;

		if(!mk[v])
			dfs(v);
	}

	ord[++l] = u;
}

int main() {
	scanf("%s%d", a + 1, &k);
	n = strlen(a + 1);

	sa_init(n);

	for(int i = 1; i <= n; i++)
		sa_extend(a[i]);

	dfs(0);

	for(int i = last; i > 0; i = st[i].link) //finding terminal nodes
		term[i] = 1;

	for(int i = 1; i <= l; i++) {
		int u = ord[i];

		dp[u] = cnt[u] = term[u];

		for(auto o : st[u].nxt) {
			int v = o.second;

			dp[u] += dp[v] + cnt[v];
			cnt[u] += cnt[v];
		}
	}

	if(k > 1LL * n * (n + 1) / 2LL) {
		printf("No such line.\n");
		return 0;
	}

	string ans = "";

	int u = 0;
	int f = 0;

	while(1) {
		if(f) {
			if(k <= cnt[u])
				break;
			k -= cnt[u];
		}

		f = 1;

		for(auto o : st[u].nxt) {
			int v = o.second;

			if(k <= dp[v]) {
				u = v;
				ans += o.first;
				break;
			}

			k -= dp[v];
		}
	}

	printf("%s\n", ans.c_str());
	return 0;
}