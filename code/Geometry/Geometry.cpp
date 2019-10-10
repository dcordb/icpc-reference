struct pt {
	int64 x, y;

	pt(int64 x, int64 y) : x(x), y(y) {}

	pt operator - (const pt &p) const {
		return pt(x - p.x, y - p.y);
	}

	pt operator + (const pt &p) const {
		return pt(x + p.x, y + p.y);
	}

	pt operator * (const double &p) const {
		return pt(x * p, y * p);
	}

	pt operator / (const double &p) const {
		return pt(x / p, y / p);
	}
};

int64 cross(pt a, pt b) {
	return a.x * b.y - a.y * b.x;
}

int64 dot(pt a, pt b) {
	return a.x * b.x + a.y * b.y;
}

int getCuad(const pt &p) { //this gets the cuadrant of a pt it is useful to compare angles
	if(p.x >= 0 && p.y >= 0)
		return 1;

	if(p.x <= 0 && p.y >= 0)
		return 2;

	if(p.x <= 0 && p.y <= 0)
		return 3;

	return 4;
}

//is a - p0 less/equal/greater than b - p0 in angle
int cmp(const pt &a, const pt &b) {
	int ca = getCuad(a - p0);
	int cb = getCuad(b - p0);

	if(ca != cb)
		return ca - cb;

	int64 c = cross(a - p0, b - p0);

	if(c > 0) //a - p0 is ccw from b (so its angle is lesser)
		return -1;

	if(c < 0)
		return 1;

	return 0; //equal angle
}

bool inTriangle(pt a, pt b, pt c, pt p) { //are pt p in triangle (a, b, c), can be on border also
	assert(cross(b - a, c - a) > 0); //checks that a, b and c are in ccw
	return cross(p - a, b - a) <= 0 && cross(p - b, c - b) <= 0 && cross(p - c, a - c) <= 0;
}

double angle(pt a) {
	return atan2(a.y, a.x);
}

//angle between vectors, gives angle from a to b from [0, 2*pi)
//for example angle between (1, 0) and (0, -1) is equal to 3*pi/2
//angle between (0, 1) and (0, -1) is equal to pi

double angleVector(pt a, pt b) {
	double ang2 = angle(a);
    double ang1 = angle(b);
    double ans = ang1 - ang2;
    if (ans < EPS) {
      ans += 2 * pi;
    }
    return ans;
}

//Lines
typedef long long type;

struct line {
	type a, b, c;

	line(type a_ = 0, type b_ = 0, type c_ = 0) {
		a = a_, b = b_, c = c_;
		fix();
	}

	line(point p1, point p2) { //dos ptos
		a = p1.y - p2.y; //comp y del vector director
		b = p2.x - p1.x; //comp x del vector director
		c = -a * p1.x - b * p1.y; //Ax + By + C = 0 (C is neg)
		fix();
	}

	void fix() { //normalizar
		type g = __gcd(labs(a), __gcd(labs(b), labs(c)));

		if(g == 0)
			return;

		a /= g, b /= g, c /= g;

		if(a < 0) {
			a *= -1;
			b *= -1;
			c *= -1;
		}

		else if(a == 0) {
			if(b < 0) {
				b *= -1;
				c *= -1;
			}

			else if(b == 0)
				c *= -1;
		}
	}

	bool operator < (const line &l) const { //ordenar
		if(a != l.a)
			return a < l.a;

		if(b != l.b)
			return b < l.b;

		return c < l.c;
	}

	bool operator == (const line &l) const {
		return a == l.a && b == l.b && c == l.c;
	}

	bool operator != (const line &l) const {
		return !(*this == l);
	}
};

pt inter(line l1, line l2) {
	type det = l1.a * l2.b - l2.a * l1.b;

	if(det == 0) {
		//rectas paralelas
		//hacer algo
	}

	double x = (0.0 + l1.b * l2.c - l2.b * l1.c) / (0.0 + det);
	double y = (0.0 + l2.a * l1.c - l1.a * l2.c) / (0.0 + det);

	return pt(x, y); //tener en cuenta que coordenadas de pt tienen que se doubles
}