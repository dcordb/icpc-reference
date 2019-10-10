#include <bits/stdc++.h>
using namespace std;

typedef long double LD;//ojo si pones eps = 0, entonces eq no pincharia cambia a fabs(x) <= EPS
const LD EPS = 1e-9;
const LD PI = acosl(-1.0);

bool zero(LD x) { return fabsl(x) < EPS; }
bool equals(LD a, LD b) { return zero(a - b); }
int cmpDouble(LD a, LD b) { return equals(a, b) ? 0 : (a < b ? -1 : +1); } //0 eq, -1 menor, 1 mayor
int sgn(LD x) { return x < 0 ? -1 : (x > 0 ? +1 : 0); }

LD sqr(LD x) { return x * x; }
LD Sqrt(LD x) { return sqrtl(max<LD>(0.0, x)); } //usar este sqrt

LD toDegree(LD angle) { return angle / PI * 180.0; }
LD toRadian(LD angle) { return angle / 180.0 * PI; }

struct Point { //se asumen puntos distintos!
	LD x, y;

	Point() {}
	Point(LD x, LD y) : x(x), y(y) {}

    Point operator + (const Point &p) const { return Point(x + p.x, y + p.y); }
	Point operator - (const Point &p) const { return Point(x - p.x, y - p.y); }
	Point operator * (const LD &v) const { return Point(x * v, y * v); }
	Point operator / (const LD &v) const { return Point(x / v, y / v); }
	bool operator == (const Point &p) const { return equals(x, p.x) && equals(y, p.y); }
	bool operator != (const Point &p) const { return !(*this == p); }
	bool operator < (const Point &p) const { return cmpDouble(x, p.x) == 0 ? y < p.y : x < p.x; }
	bool operator > (const Point &p) const { return p < *this; }


	Point rotateCCW(LD ang) { return Point(x * cos(ang) - y * sin(ang), x * sin(ang) + y * cos(ang)); }

};

Point RotateCCW90(Point p) { return Point(-p.y , p.x); }
Point RotateCW90(Point p)  { return Point(p.y , -p.x); }
Point max(const Point &a, const Point &b) { return a > b ? a : b; }
Point min(const Point &a, const Point &b) { return a < b ? a : b; }

struct Vector {
	LD x, y;

	Vector() {}
	Vector(LD x, LD y) : x(x), y(y) {}
	Vector(Point a, Point b) { //inicio, fin
		x = b.x - a.x;
		y = b.y - a.y;
		//assert(!zero(x) || !zero(y)); //vector nulo no valido
	}

    //agregado por Mel
    Vector(Point a){
       x = a.x;
       y = a.y;
    }

	Vector operator + (const Vector &v) const { return Vector(x + v.x, y + v.y); }
	Vector operator - (const Vector &v) const { return Vector(x - v.x, y - v.y); }
	Vector operator * (const LD &v) const { return Vector(x * v, y * v); }
	Vector operator / (const LD &v) const { return Vector(x / v, y / v); }

	LD getNorm() { return Sqrt(sqr(x) + sqr(y)); }
	LD getNormCuadr() { return sqr(x) + sqr(y); }// agregado!!!! por Mel
	Vector getVectorNormal() { return Vector(-y, x); }

	int getCuad() {
		if(cmpDouble(x, 0) >= 0 && cmpDouble(y, 0) >= 0)
			return 1;

		if(cmpDouble(x, 0) <= 0 && cmpDouble(y, 0) >= 0)
			return 2;

		if(cmpDouble(x, 0) <= 0 && cmpDouble(y, 0) <= 0)
			return 3;

		return 4;
	}

	//regresa angulo con el eje x en el intervalo [-pi, pi]
	LD orientedAngleWithAxis() { return atan2(y, x); }

	//regresa angulo con el eje x en el intervalo [0, 2 * pi)
	LD angleWithAxis() {
		LD ang = orientedAngleWithAxis();
		return getCuad() <= 2 ? ang : 2.0 * PI + ang;
	}


	Vector rotateCCW(LD ang) { return Vector(x * cos(ang) - y * sin(ang), x * sin(ang) + y * cos(ang)); }

	Point toPoint() { return Point(x, y); }

};

// Aporte revisar

Vector Scale(Vector v, LD s) { // nonnegative s = [<1 .. 1 .. >1]
    return Vector(v.x * s, v.y * s); } // shorter.same.longer

Point Translate(Point p, Vector v) { // translate p according to v
    return Point(p.x + v.x , p.y + v.y); }

Vector RotateCCW90(Vector p) { return Vector(-p.y , p.x); }
Vector RotateCW90(Vector p)  { return Vector(p.y , -p.x); }

//para debuggear
ostream & operator << (ostream &os, const Point &P) {
	os << P.x << ' ' << P.y;
	return os;
}

ostream & operator << (ostream &os, const Vector &P) {
	os << P.x << ' ' << P.y;
	return os;
}

LD cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
LD dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }

LD dist(Point a, Point b) { return Vector(a, b).getNorm(); }
LD dist2(Point a, Point b) { return sqr(a.x - b.x) + sqr(a.y - b.y); }

bool areCollinear(Vector a, Vector b) { return zero(cross(a, b)); }
bool arePerpendicular(Vector a, Vector b) { return zero(dot(a, b)); }

//angle from vector A to B

bool isAng_0_Degrees(Vector a, Vector b) { return areCollinear(a, b) && cmpDouble(dot(a, b), 0) >= 0; } //inclusive, because null vector
bool isAng_90_Degrees(Vector a, Vector b) { return arePerpendicular(a, b) && cmpDouble(cross(a, b), 0) >= 0; }
bool isAng_180_Degrees(Vector a, Vector b) { return areCollinear(a, b) && cmpDouble(dot(a, b), 0) <= 0; }
bool isAng_270_Degrees(Vector a, Vector b) { return arePerpendicular(a, b) && cmpDouble(cross(a, b), 0) <= 0; }

/*

Dados los vectores A y B:

-el angulo orientado entre A y B es el angulo que se obtiene al rotar el vector A hasta que llegue al B
-por ejemplo si tenemos A = (1, 1), B = (1, -1) entonces ang = 270 grados

-el angulo no orientado entre A y B es el angulo minimo que se obtiene al rotar A hacia B o B hacia A.
-por ejemplo si tenemos A = (1, 1), B = (1, -1) entonces ang = 90 grados

*/

//vector cuyo angulo es igual al angulo desde A hasta B (orientado)
Vector orientedVectorAngle(Vector a, Vector b) { return Vector(dot(a, b), cross(a, b)); } //ojo magnitudes al cuadrado
//vector cuyo angulo es igual al angulo desde A hasta B (NO orientado)
Vector notOrientedVectorAngle(Vector a, Vector b) { return Vector(dot(a, b), fabsl(cross(a, b))); } //ojo magnitudes al cuadrado

LD orientedAngleBetweenVectors(Vector a, Vector b) { return orientedVectorAngle(a, b).angleWithAxis(); }

LD notOrientedAngleBetweenVectors(Vector a, Vector b) { return notOrientedVectorAngle(a, b).angleWithAxis(); }

//ordena vectores en orden CCW por angulo
bool cmpVectors(Vector a, Vector b) {
	int ca = a.getCuad();
	int cb = b.getCuad();

	if(ca != cb)
		return ca < cb;

	LD c = cross(a, b);

	return cmpDouble(c, 0) > 0;
}

//ojo, se asumen lineas no degeneradas, es decir pto pto no es una linea valida
struct Line {
	Point p;
	Vector v;

	Line(Point a, Point b) {
		v = Vector(a, b);
		p = a;
	}

	Line(Point p, Vector v) : p(p), v(v) {}

	Line(LD a, LD b, LD c) { //entrada en forma Ax + By + C = 0
		v = Vector(a, b).getVectorNormal(); //vector director

		//here p is an arbitrary point that belongs to line

		if(zero(b))
			p = Point(-c / a, 0);

		else p = Point(0, -c / b);
	}

	Line(LD a, LD b, LD c, Point p_) {
		v = Vector(a, b).getVectorNormal();
		p = p_;
	}

	vector <LD> toCartesianForm() {
		Vector n = v.getVectorNormal();
		vector <LD> r = { n.x, n.y, -n.x * p.x - n.y * p.y }; //regresa en la forma Ax + By + C = 0
		return r;
	}
};



using Segment = Line;
using Ray = Line;

bool areLinesParallel(Line a, Line b) {
	return zero(cross(a.v, b.v));
}

bool areLinesCollinear(Line a, Line b) {
	return areLinesParallel(a, b) && zero(cross(a.v, Vector(a.p, b.p)));
}

/*
	Punto en linea, segmento, rayo
*/

bool onLine(Point p, Line l) {
	return zero(cross(l.v, Vector(l.p, p)));
}

//puntos extremos de segmento (utilidad)
vector <Point> getSegmentEP(Segment s) {
	return { s.p, (Vector(s.p.x, s.p.y) + s.v).toPoint() };
}

bool onSegment(Point p, Segment s) {
	if(!onLine(p, s))
		return false;

	auto o = getSegmentEP(s);

	Vector u(p, o[0]);
	Vector v(p, o[1]);

	return cmpDouble(dot(u, v), 0) <= 0;
}

bool onRay(Point p, Ray r) {
	return onLine(p, r) && isAng_0_Degrees(r.v, Vector(r.p, p));
}

/*
	Esto devuelve el valor de t para dos lineas a, b,
	nota que siempre hay que hacer getFI(a, b) y getFI(b, a)
	para tener ambos t

	si t >= 0 rayo
	si 0 <= t <= 1 segmento
	si no recta
*/

pair <LD, LD> getFractionIntersection(Line a, Line b) {
	LD num = cross(Vector(a.p, b.p), b.v);
	LD den = cross(a.v, b.v);

	if(cmpDouble(den, 0) < 0) {
		num *= -1;
		den *= -1;
	}

	return { num, den };
}

/*
	Chequear por interseccion de segmentos, lineas, rayos
	y cualquier combinacion de ellos.

	Ojo aca, si se cambia lo q se quiere interceptar hay que cambiar I.
*/

bool areSegmentIntersect(Segment a, Segment b) {
	if(areLinesCollinear(a, b)) {
		bool r = false;

		for(auto o : getSegmentEP(a))
			r |= onSegment(o, b);

		for(auto o : getSegmentEP(b))
			r |= onSegment(o, a);

		return r;
	}

	if(areLinesParallel(a, b))
		return false;

	//estas son las fracciones de los valores de t
	auto f1 = getFractionIntersection(a, b); //t1 de a, b
	auto f2 = getFractionIntersection(b, a); //t2 de b, a

	assert(cmpDouble(f1.second, 0) >= 0); //denominador positivo
	assert(cmpDouble(f2.second, 0) >= 0);

	//esto es I, es necesario modificar esto si se pasa una linea o rayo
	//return cmpDouble(f1.first, 0) >= 0 && cmpDouble(f1.first, f1.second) <= 0 && cmpDouble(f2.first, 0) >= 0 && cmpDouble(f2.first, f2.second) <= 0;
	return cmpDouble(f1.first, 0) >= 0 && cmpDouble(f2.first, 0) >= 0;
}


//chequear por interseccion primero en caso de linea, segmento o rayo!!
Point getIntersect(Line a, Line b) {
	auto f = getFractionIntersection(a, b);
	return (Vector(a.p.x, a.p.y) + (a.v * f.first) / f.second).toPoint();
}

//asumiendo a != b
Point ProjectPointLine(Point a, Point b, Point c) {
	return a + (b - a)*dot(c - a, b - a)/dot(b - a, b - a);
}

Point ProjectPointSegment(Point a, Point b, Point c) {
	LD r = dot(b - a,b - a);

	if (fabs(r) < EPS) 
		return a;

	r = dot(c - a, b - a)/r;
	
	if (r < 0) 
		return a;
	
	if (r > 1) 
		return b;
	
	return a + (b - a)*r;
}

Point ProjectPointRay(Point a, Point b, Point c) {
	LD r = dot(b - a,b - a);

	if (fabs(r) < EPS) 
		return a;

	r = dot(c - a, b - a)/r;
	
	if (r < 0) 
		return a;
	
	return a + (b - a)*r;
}


// los puntos a,b determinan la linea
Point Reflexion(Point a, Point b, Point c){
      Point res = ProjectPointLine(a, b, c);
      res = res * 2 - c;
     return res;
}

//Aqui empieza Circulo
/*
     Law of Cosines (dado los 3 lados, determinar el angulo entre cualquiera de ellos)
      c*c = a*a + b*b - 2*a*b*cos(alpha)

     Law of Sines
       a/sin(alpha) = b/sin(beta) = c/sin(theta) = 2*R
       R the radus of the circumcircle

     A = r*r
     L = 2 * Pi * r
     Arc = alpha/360 * L
     Sector = alpha/360 * A
     Chord = sqrt(2 * r * r * (1 - cos(a))) by the Law of cosines
     AreaSegment =  AreaCorrespSector - AreaIsoscelesTriangle

     Heron's Formula = sqrt( s * (s - a) * (s - b) * (s - c) )
     *
*/


//Given 2 points on the circle (p1 and p2) and radius r of the corresponding circle, we
//can determine the location of the centers (c1 and c2) of the two possible circles
//no esta chequeado!!!
bool circle2PtsRad(Point p1, Point p2, LD r, Point &c) {

    if(p1==p2) return true; //hay infinitos que se intersectan y solo un par que son tangentes entre si

	LD d2 = dist2(p1, p2);
	LD det = r * r / d2 - 0.25;

	if (cmpDouble(det, 0) < 0)
		return false;

	LD h = Sqrt(det);

	c.x = (p1.x + p2.x) * 0.5 + (p1.y - p2.y) * h;
	c.y = (p1.y + p2.y) * 0.5 + (p2.x - p1.x) * h;

	return true;
} //para obtener el otro centro, intercambia p2 y p1

// cambiar despues para hacerlo general para poligonos
LD perimeter(LD a, LD b, LD c){
   return a + b + c;
}

LD area(LD a, LD b, LD c){ // por la formula de Heron

	LD s = 0.5 * perimeter(a, b, c);
    return Sqrt(s * (s - a) * (s - b) * (s - c));
}

//A triangle with area A and semi-perimeter s has an inscribed circle (incircle) with radius r = A/s
LD rInCircle(LD ab, LD bc, LD ca) {
	return area(ab, bc, ca) / (0.5 * perimeter(ab, bc, ca));
}

LD rInCircle(Point a, Point b, Point c) {
	return rInCircle(Sqrt(dist2(a, b)), Sqrt(dist2(b, c)), Sqrt(dist2(c, a)));
}

//A triangle with 3 sides: a, b, c and area A has an circumscribed circle (circumcircle)
//with radius R = a * b * c/(4 * A)

LD rCircumCircle(LD ab, LD bc, LD ca){
	return ab * bc * ca / (4.0 * area(ab, bc, ca));
}

LD rCircumCircle(Point a, Point b, Point c){
	return rCircumCircle(Sqrt(dist2(a, b)), Sqrt(dist2(b, c)), Sqrt(dist2(c, a)));
}


// returns 1 if there is an inCircle center, returns 0 otherwise
// if this function returns 1, ctr will be the inCircle center
// and r is the same as rInCircle
// el centro del circulo inscrito es el el punto de interseccion de las
// bisectrices del triangulo
bool cinCircle(Point p1, Point p2, Point p3, Point &ctr, LD &r) {

	r = rInCircle(p1, p2, p3);

	if (zero(r))
		return 0; // no inCircle center


	LD ratio = Sqrt(dist2(p1, p2) / dist2(p1, p3));

	Point p = Translate(p2, Scale(Vector(p2, p3), ratio / (1 + ratio)));
	Line l1(p1, p);

	ratio = Sqrt(dist2(p2, p1) / dist2(p2, p3));

	p = Translate(p1, Scale(Vector(p1, p3), ratio / (1 + ratio)));

	Line l2(p2, p);

	if(areLinesParallel(l1, l2)) return 0;

	ctr = getIntersect(l1, l2); // get their intersection point

    return 1;
}


//check if a point is inside a circle
//tested
int insideCircle(Point p, Point c, LD r) {

    LD Euc = dist2(p, c), rSq = r * r; // all integer
    
    return cmpDouble(Euc, rSq); 
 
} //inside/border/outside



// compute center of circle given three points
// tener cuidado si son colineares los puntos, no existe circulo!
//tested
Point ComputeCircleCenter(Point a, Point b, Point c) {
  b = (a + b) * 0.5;
  c = (a + c) * 0.5;
  return getIntersect(Line(b, b + RotateCW90(a - b)), Line(c, c + RotateCW90(a - c)));
}

// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
vector<Point> CircleCircleIntersection(Point a, Point b, LD r, LD R) {
	vector<Point> ret;

	LD d = Sqrt(dist2(a, b));

	if (d > r + R || cmpDouble(d + min(r, R) , max(r, R)) < 0) return ret;

	LD x = (d * d - R * R + r * r)/(2 * d);

	LD y = Sqrt(r * r - x * x);

	Point v = (b - a) / d;
	ret.push_back(a + v * x + RotateCCW90(v) * y);

	if (y > 0)
	   ret.push_back(a + v * x - RotateCCW90(v) * y);

	return ret;
}


// compute intersection of line through points a and b with
// circle centered at c with radius r > 0
vector<Point> CircleLineIntersection(Point a, Point b, Point c, LD r) {
  vector<Point> ret;
  b = b - a;
  a = a - c;
  LD A = dot(b, b);
  LD B = dot(a, b);
  LD C = dot(a, a) - r*r;
  LD D = B*B - A*C;

  if (D < -EPS) return ret;
      ret.push_back(c + a + b * (-B + sqrt(D + EPS))/A);

  if (D > EPS)
    ret.push_back(c + a + b * (-B - sqrt(D))/A);

  return ret;
}


// Aqui empieza lo de poligono


// determine if point is in a possibly non-convex polygon (by William
// Randolph Franklin); returns 1 for strictly interior points, 0 for
// strictly exterior points, and 0 or 1 for the remaining points.
// Note that it is possible to convert this into an *exact* test using
// integer arithmetic by taking care of the division appropriately
// (making sure to deal with signs properly) and then by writing exact
// tests for checking point on polygon boundary

bool PointInPolygon(const vector<Point> &p, Point q) {
  bool c = 0;

  for (int i = 0; i < (int)p.size(); i++){
    int j = (i + 1) % p.size();
    if (((p[i].y <= q.y && q.y < p[j].y) || (p[j].y <= q.y && q.y < p[i].y)) && (q.x < p[i].x + (p[j].x - p[i].x) * (q.y - p[i].y) / (p[j].y - p[i].y)))
         c = !c;
  }

  return c;

}


// line segment p-q intersect with line A-B.
Point lineIntersectSeg(Point p, Point q, Point A, Point B) {

	double a = B.y - A.y;
	double b = A.x - B.x;
	double c = B.x * A.y - A.x * B.y;
	double u = fabs(a * p.x + b * p.y + c);
	double v = fabs(a * q.x + b * q.y + c);

 return Point((p.x * v + q.x * u) / (u+v), (p.y * v + q.y * u) / (u+v)); 
}

// cuts polygon Q along the line formed by point a -> point b
// (note: the last point must be the same as the first point)
vector<Point> cutPolygon(Point a, Point b, const vector<Point> &Q) {
	vector<Point> P;
	
	for (int i = 0; i < (int)Q.size(); i++) {
		LD left1 = cross(Vector(a, b), Vector(a, Q[i])), left2 = 0;
		if (i != (int)Q.size()-1) left2 = cross(Vector(a, b), Vector(a, Q[i+1]));
		if (left1 > -EPS) P.push_back(Q[i]); // Q[i] is on the left of ab
		if (left1 * left2 < -EPS) // edge (Q[i], Q[i+1]) crosses line ab
		P.push_back(lineIntersectSeg(Q[i], Q[i+1], a, b));
    }

	if (!P.empty() && !(P.back() == P.front()))

	P.push_back(P.front()); // make P's first point = P's last point

	return P; 
}

int main() {
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);	

	return 0;
}

