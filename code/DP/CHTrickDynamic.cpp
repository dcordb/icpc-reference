//dynamic convex hull trick
//esta implementacion no depende del orden de las pendientes ni de nada
//okok

const int64 is_query = -(1LL<<62);
struct Line {
    int64 m, b;
    mutable function<const Line*()> succ;
    bool operator<(const Line& rhs) const { //this is for maximum (pendientes crecientes), for minimum (pendientes decrecientes) change < in lines 6 and 10 to >
        if (rhs.b != is_query) return m < rhs.m; //here
        const Line* s = succ();
        if (!s) return 0;
        int64 x = rhs.m;
        return b - s->b < (s->m - m) * x; //here
    }
};
struct HullDynamic : public multiset<Line> {
    bool bad(iterator y) {
        auto z = next(y);
        if (y == begin()) {
            if (z == end()) return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end()) return y->m == x->m && y->b <= x->b;
        return (x->b - y->b)*(z->m - y->m) >= (y->b - z->b)*(y->m - x->m);
    }
    void insert_line(int64 m, int64 b) {
        auto y = insert({ m, b });
        y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y)) { erase(y); return; }
        while (next(y) != end() && bad(next(y))) erase(next(y));
        while (y != begin() && bad(prev(y))) erase(prev(y));
    }
    int64 eval(int64 x) {
        auto l = *lower_bound((Line) { x, is_query });
        return l.m * x + l.b;
    }
} h; //inicializar: h = HullDynamic()