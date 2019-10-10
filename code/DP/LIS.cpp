//LIS O(n log k)
//tested on uva00481
//para obtener LDS reverse the array a

const int MAX = 1e6 + 5;
int n, m, l, a[MAX], ant[MAX], ans[MAX], res[MAX]; //elementos, ant es el id anterior a i en el lis, ans es el lis hasta pos i, res es el lis ok
pair <int, int> v[MAX]; //arreglo de numero, id, para recuperar la respuesta

int main() {
	//leyendo entrada
	while(scanf("%d", &a[++n]) != EOF);

	n--;
	////////////////////////////////////////////////////////

	for(int i = 1; i <= n; i++) {
		int p = lower_bound(v + 1, v + m + 1, make_pair(a[i], 0)) - v; //para permitir elementos iguales cambiar el 0 por INF, ej: 1e9
		v[p] = { a[i], i };

		if(p == m + 1)
			m++;

		ant[i] = v[p - 1].second;
		ans[i] = ans[ant[i]] + 1;
	}

	//esta parte es especifica del uva00481

	int pos = 0;
	for(int i = n; i > 0; i--) {
		if(ans[i] == m) {
			pos = i;
			break;
		}
	}

	//recuperando el lis, la respuesta queda en res
	while(pos > 0) {
		res[++l] = a[pos];
		pos = ant[pos];
	}

	return 0;
}