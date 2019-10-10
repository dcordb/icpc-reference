//Prim O(N^2)

#include <bits/stdc++.h>
using namespace std;

const int
	MAX = 1e4 + 5,
	INF = 2e9;
int n, mst[MAX], cost[MAX];

struct par {
	int x, y;
} pt[10005];

int main() {
	scanf("%d", &n);

	for(int i = 1; i <= n; i++)
		scanf("%d%d", &pt[i].x, &pt[i].y);

	//cost[1] = 0, nodo inicio de prim
	for(int i = 2; i <= n; i++)
		cost[i] = INF;

	long long ans = 0;
	for(int i = 1; i <= n; i++) {
		int best = INF;
		int opt = -1;

		for(int j = 1; j <= n; j++) {
			if(!mst[j] && cost[j] < best) {
				best = cost[j];
				opt = j;
			}
		}

		mst[opt] = 1; //marcador de nodos q estan en el mst
		ans += 2 * best;

		for(int j = 1; j <= n; j++) { //actualiza costo del resto de los nodos
			if(mst[j])
				continue;

			int d = abs(pt[opt].x - pt[j].x) + abs(pt[opt].y - pt[j].y); //costo de arista

			if(d < cost[j])
				cost[j] = d;
		}
	}

	printf("%lld\n", ans);
	return 0;
}