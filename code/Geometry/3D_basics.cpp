#include <bits/stdc++.h>
using namespace std;

typedef long double LD;
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
	LD x, y, z;

	Point() {}
	Point(LD x, LD y, LD z) : x(x), y(y), z(z) {}

    Point operator + (const Point &p) const { return Point(x + p.x, y + p.y, z + p.z); }
	Point operator - (const Point &p) const { return Point(x - p.x, y - p.y, z - p.z); }
	Point operator * (const LD &v) const { return Point(x * v, y * v, z * v); }
	Point operator / (const LD &v) const { return Point(x / v, y / v, z / v); }
	bool operator == (const Point &p) const { return equals(x, p.x) && equals(y, p.y) && equals(z, p.z); }
	bool operator != (const Point &p) const { return !(*this == p); }


};

struct Vector {
	LD x, y, z;

	Vector() {}
	Vector(LD x, LD y, LD z) : x(x), y(y), z(z) {}
	Vector(Point a, Point b) { //inicio, fin
		x = b.x - a.x;
		y = b.y - a.y;
		z = b.z - a.z;
		//assert(!zero(x) || !zero(y)); //vector nulo no valido
	}
     
    Vector(Point a){
	    x = a.x;
	    y = a.y;
	    z = a.z;
	}
	
	Vector operator + (const Vector &v) const { return Vector(x + v.x, y + v.y, z + v.z); }
	Vector operator - (const Vector &v) const { return Vector(x - v.x, y - v.y, z - v.z); }
	Vector operator * (const LD &v) const { return Vector(x * v, y * v, z * v); }
	Vector operator / (const LD &v) const { return Vector(x / v, y / v, z / v); }
    bool operator == (const Vector &p) const { return equals(x, p.x) && equals(y, p.y) && equals(z, p.z); }
	bool operator != (const Vector &p) const { return !(*this == p); }
    
	LD getNorm() { return Sqrt(sqr(x) + sqr(y) + sqr(z)); }
	LD getNormCuadr() { return sqr(x) + sqr(y) + sqr(z); }

    
    Point toPoint() { return Point(x, y, z); }

};

// Aporte revisar

Vector Scale(Vector v, LD s) { // nonnegative s = [<1 .. 1 .. >1]
    return Vector(v.x * s, v.y * s, v.z * s); } // shorter.same.longer

Point Translate(Point p, Vector v) { // translate p according to v
    return Point(p.x + v.x , p.y + v.y, p.z + v.z); }

Vector cross(Vector a, Vector b) { return Vector(a.y * b.z - a.z * b.y,  - a.x * b.z + a.z * b.x, a.x * b.y - a.y * b.x); }
LD dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y + a.z * b.z; }

LD dist(Point a, Point b) { return Vector(a, b).getNorm(); }
LD dist2(Point a, Point b) { return sqr(a.x - b.x) + sqr(a.y - b.y) + sqr(a.z - b.z); }

struct Line {
	Point p;
	Vector v;

	Line(Point a, Point b) {
		v = Vector(a, b);
		p = a;
	}

	Line(Point p, Vector v) : p(p), v(v) {}
    
	
};

struct Segment {
  Point P0, P1;
};

//ojo, se asumen lineas no degeneradas, es decir pto pto no es una linea valida
struct Plane {
	Point p;
	Vector n;

	Plane(Point a, Point b, Point c) {
		Point null(0,0,0);
		n = cross(Vector(null,b - a), Vector(null,c - a));
		p = a;
	}

	Plane(Point p, Vector n) : p(p), n(n) {}
};

int Intersect3D_SegmPlane(Segment s, Plane Pn, Point &p){
    
    Vector u = Vector(s.P1) - Vector(s.P0);
    Vector w = Vector(s.P0) - Vector(Pn.p);

    LD D = dot(Pn.n, u);
    LD N = -dot(Pn.n, w);

    if (zero(D)) {           // segment is parallel to plane
        if (N == 0)                      // segment lies in plane
            return 2;
        else
            return 0;                    // no intersection
    }
    
    // they are not parallel
    // compute intersect param
    LD sI = N / D;
    if (sI < 0 || sI > 1)
        return 0;                        // no intersection

    p = s.P0 + ((u.toPoint()) * sI); // compute segment intersect point
    return 1;
}

int Intersect3D_2Planes(Plane Pn1, Plane Pn2, Line &L){
   
    Vector u = cross(Pn1.n, Pn2.n); // vector perpendicular a n1 y n2
    LD ax = (u.x >= 0 ? u.x : -u.x);
    LD ay = (u.y >= 0 ? u.y : -u.y);
    LD az = (u.z >= 0 ? u.z : -u.z);

    // test if the two planes are parallel
    if (zero(ax + ay + az)) {        // Pn1 and Pn2 are near parallel
        // test if disjoint or coincide
        Vector v = Pn2.p -  Pn1.p;
        if (equals(dot(Pn1.n, v),0))          // Pn2.V0 lies in Pn1
            return 1;                    // Pn1 and Pn2 coincide
        else
            return 0;                    // Pn1 and Pn2 are disjoint
    }

    // Pn1 and Pn2 intersect in a line
    // first determine max abs coordinate of cross product
    int maxc;  // max coordinate
    if (ax > ay) {
        if (ax > az)
             maxc =  1;
        else 
             maxc = 3;
    }
    else {
        if (ay > az)
             maxc =  2;
        else 
             maxc = 3;
    }

    // next, to get a point on the intersect line
    // zero the max coord, and solve for the other two
    Point iP; // intersect point
    LD d1, d2; // the constants in the 2 plane equations
    d1 = -dot(Pn1.n, Pn1.p);  // note: could be pre-stored  with plane
    d2 = -dot(Pn2.n, Pn2.p);  // ditto

    switch (maxc) { // select max coordinate
    if(maxc == 1){         // intersect with x=0
			iP.x = 0;
			iP.y = (d2*Pn1.n.z - d1*Pn2.n.z) /  u.x;
			iP.z = (d1*Pn2.n.y - d2*Pn1.n.y) /  u.x;
    }
    else
    {
		if(maxc == 2){ //intersect with y=0
			iP.x = (d1*Pn2.n.z - d2*Pn1.n.z) /  u.y;
			iP.y = 0;
			iP.z = (d2*Pn1.n.x - d1*Pn2.n.x) /  u.y; 
		}
		else{
		    // intersect with z=0
			iP.x = (d2*Pn1.n.y - d1*Pn2.n.y) /  u.z;
			iP.y = (d1*Pn2.n.x - d2*Pn1.n.x) /  u.z;
			iP.z = 0;
		} 
	}
        
    }
    L.v = Vector(iP, iP + u.toPoint());
    L.p = iP;
    
    return 2;
    
}

int intersect3D_RayTriangle( Segment R, vector<Point> T, Point &I )
{
    Vector u, v, n;              // triangle vectors
    Vector dir, w0, w;           // ray vectors
    LD r, a, b;              // params to calc ray-plane intersect

    // get triangle edge vectors and plane normal
    u = T[1] - T[0];
    v = T[1] - T[0];
    n = cross(u , v);              // cross product
    if (n == Vector(0,0,0))             // triangle is degenerate
        return -1;                  // do not deal with this case

    dir = R.P1 - R.P0;              // ray direction vector
    w0 = R.P0 - T[0];
    a = -dot(n , w0);
    b = dot(n , dir);
    if (zero(b)) {     // ray is  parallel to triangle plane
        if (a == 0)                 // ray lies in triangle plane
            return 2;
        else return 0;              // ray disjoint from plane
    }

    // get intersect point of ray with triangle plane
    r = a / b;
    if (r < 0.0)                    // ray goes away from triangle
        return 0;                   // => no intersect
    // for a segment, also test if (r > 1.0) => no intersect

    I = R.P0 + (dir.toPoint()) * r;            // intersect point of ray and plane

    // is I inside T?
    LD uu, uv, vv, wu, wv, D;
    uu = dot(u,u);
    uv = dot(u,v);
    vv = dot(v,v);
    w = I - T[0];
    wu = dot(w,u);
    wv = dot(w,v);
    D = uv * uv - uu * vv;

    // get and test parametric coords
    LD s, t;
    s = (uv * wv - vv * wu) / D;
    if (s < 0.0 || s > 1.0)         // I is outside T
        return 0;
    t = (uv * wu - uu * wv) / D;
    if (t < 0.0 || (s + t) > 1.0)  // I is outside T
        return 0;

    return 1;                       // I is in T
}

int main() {
	return 0;
}


