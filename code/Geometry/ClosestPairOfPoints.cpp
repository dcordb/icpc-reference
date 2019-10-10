//Closest Pair Of Points O(nlogn)

struct pt {
	int x, y;

	pt() {}

	pt(int x, int y) : x(x), y(y) {}
} p[100005];

bool operator < (const pt &a, const pt &b) { //comparador del multiset
	if(a.y != b.y)
		return a.y < b.y;
	return a.x < b.x;
}

bool cmp(const pt &a, const pt &b) { //comparador para arreglo p
	if(a.x != b.x)
		return a.x < b.x;
	return a.y < b.y;
}

int n;
multiset <pt> s;

int dist(const pt &a, const pt &b) { //metrica especifica del problema
	return max(abs(a.x - b.x), abs(a.y - b.y));
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%d%d", &p[i].x, &p[i].y);

	sort(p + 1, p + n + 1, cmp);

	s.clear(); //limpiar s, importante

	int ans = 1e9;
	for(int i = 1, j = 1; i <= n; i++) {
		while(p[i].x - p[j].x > ans) {
			s.erase(s.find(p[j]));
			j++;
		}

		auto l = s.lower_bound(pt(-1e9, p[i].y - ans - 1));
		auto u = s.upper_bound(pt(1e9, p[i].y + ans + 1));

		for(; l != u; l++)
			ans = min(ans, dist(p[i], *l));

		s.insert(p[i]);
	}

	printf("%d\n", ans);
	return 0;
}