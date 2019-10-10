//convex hull trick with a set
//this can be used if the x of queries are not in order
//time complexity will be O(rectas log rectas)
//si pendientes son crecientes buscara upper hull (maximo)
//si pendientes son decrecientes buscara lower hull (minimo)

namespace CH {
	const double eps = 1e-9;
	const int64 INF = 1e18;

	struct rect {
		int64 n, m;

		rect(int64 n = 0, int64 m = 0) : n(n), m(m) {}

		int64 eval(int64 x) {
			return m * x + n;
		}
	};

	struct data {
		double x;
		int id;

		data(double x = 0, int id = 0) : x(x), id(id) {}

		bool operator < (const data &d) const {
			return x + eps < d.x;
		}
	};

	int k, opt;
	rect stk[MAX];
	multiset <data> s;

	void init() { //call this first
		k = 0, opt = 1;
		s.clear();
	}

	double inter(rect a, rect b) { //x-intersection between two rects
		return (0.0 + a.n - b.n) / (0.0 + b.m - a.m);
	}

	bool bad_line(rect l1, rect l2, rect l3) {
		return (l1.n - l3.n) * (l2.m - l1.m) < (l3.m - l1.m) * (l1.n - l2.n);
	}

	void add(int64 n, int64 m) {
		while(k > 1 && bad_line(stk[k - 1], stk[k], rect(n, m))) {
			auto obj = data(inter(stk[k], stk[k - 1]), k);
			s.erase(s.find(obj));
			k--;
		}

		stk[++k] = rect(n, m);

		if(k == 1)
			s.insert(data(-INF, k));

		else s.insert(data(inter(stk[k], stk[k - 1]), k));
	}

	int64 query(int64 x) {
		if(k == 0)
			return 0;

		auto it = --s.upper_bound(data(x, 0));
		return stk[it -> id].eval(x);
	}
};