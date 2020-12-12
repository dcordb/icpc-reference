/*
A persistent segment tree. Note that this one uses 0 to represent null node.
0-indexed everywhere and [a, b] intervals
*/

struct node {
    int a, b;        //range of node: [a, b]
    int mx;
    int l, r;        //children

    node(int a, int b, int mx, int l = 0, int r = 0) :
        a(a), b(b), mx(mx), l(l), r(r) {}
};

template <typename T>
struct stree {
    vector <T> t;

    stree() {
        // null node
        t.push_back(T(-1, -1, 0));
    }

    int new_node(const T &x) {
        t.push_back(x);
        return (int) t.size() - 1;
    }

    int build(int a, int b) { // returns node created
        if(a == b)
            return new_node(T(a, b, 0));

        int m = (a + b) >> 1;

        int nl = build(a, m);
        int nr = build(m + 1, b);

        return new_node(T(a, b, 0, nl, nr));
    }

    int upd(int x, int p, int v) {
        if(t[x].a > p || t[x].b < p)
            return x;

        if(t[x].a == t[x].b)
            return new_node(T(t[x].a, t[x].b, v));

        int nl = upd(t[x].l, p, v);
        int nr = upd(t[x].r, p, v);

        int mx = max(t[nl].mx, t[nr].mx);
    
        return new_node(T(t[x].a, t[x].b, mx, nl, nr));
    }

    int query(int x, int a, int b) {
        if(t[x].a > b || t[x].b < a)
            return 0;

        if(t[x].a >= a && t[x].b <= b)
            return t[x].mx;

        return max(query(t[x].l, a, b), query(t[x].r, a, b));
    }
};

/*
create array of roots and initialize the 0-th tree, for example:

stree st;
root[0] = st.build(0, n - 1)

then do updates and queries to create/modify trees.
*/