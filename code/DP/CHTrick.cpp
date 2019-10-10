/*this is for maximum

para maximo tiene que cumplir que las pendientes sean crecientes
para minimo tiene que cumplir que las pendientes sean decrecientes

en ambos casos pueden haber pendientes iguales

esta implementacion (con dos punteros)
es para cuando las x de las queries estan en orden creciente (pueden haber iguales)
*/
namespace CH {
	struct rect {
		int64 n, m;

		rect(int64 n = 0, int64 m = 0) : n(n), m(m) {}

		int64 eval(int64 x) {
			return m * x + n;
		}
	};

	int k, opt; //tamanno de pila y puntero a funcion optima
	rect stk[MAX];

	void init() { //llamar a esta funcion para inicializar
		k = 0, opt = 1;
	}

	bool bad_line(rect l1, rect l2, rect l3) {
		return (l1.n - l3.n) * (l2.m - l1.m) < (l3.m - l1.m) * (l1.n - l2.n);
	}

	void add(int64 n, int64 m) {
		while(k > 1 && bad_line(stk[k - 1], stk[k], rect(n, m)))
			k--;

		stk[++k] = rect(n, m);
	}

	int64 query(int64 x) {
		if(k == 0)
			return 0;

		if(opt > k)
			opt = k;

		while(opt < k && stk[opt].eval(x) <= stk[opt + 1].eval(x)) //for minimum change <= to >=
			opt++;

		return stk[opt].eval(x);
	}
};