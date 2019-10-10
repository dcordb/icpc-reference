#include <bits/stdc++.h>
using namespace std;

const int
	MAXN = 1005,
	MAXM = 205,
	INF = 1e9;
int n, m, t[MAXN][MAXN], dp[MAXM][MAXN];

int cost(int i, int j) {
	return (t[j][j] - t[j][i - 1] - t[i - 1][j] + t[i - 1][i - 1]) >> 1;
}

void get(int k, int l, int r, int optL, int optR) {
	if(l > r)
		return;

	int i = (l + r) >> 1;
	int opt = -1;

	for(int j = max(optL, 0); j <= optR && j < i; j++) {
		int ct = dp[k - 1][j] + cost(j + 1, i);

		if(ct < dp[k][i]) {
			dp[k][i] = ct;
			opt = j;
		}
	}

	get(k, l, i - 1, optL, opt);
	get(k, i + 1, r, opt, optR);
}

int main() {
	//ios_base::sync_with_stdio(0);
	//cin.tie(0);

	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	scanf("%d%d\n", &n, &m);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			char c = getchar();
			getchar();
			t[i][j] = t[i - 1][j] + t[i][j - 1] - t[i - 1][j - 1] + (c - '0');
		}
	}

	for(int i = 0; i <= m; i++)
		for(int j = 0; j <= n; j++)
			dp[i][j] = INF;

	for(int i = 1; i <= n; i++)
		dp[1][i] = cost(1, i);

	for(int k = 2; k <= m; k++)
		get(k, 1, n, 0, n);

	printf("%d\n", dp[m][n]);
	return 0;
}