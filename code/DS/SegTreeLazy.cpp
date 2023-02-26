/*
Segment Tree Data Structure

This is a template for segment tree. This shows an implementation of
- add in a range `x`
- tell sum in a range
- tell min in a range

So this one implements lazy.

Whole structure is 0-indexed use inclusive intervals [a, b].
*/

const int INF = numeric_limits<int>::max();

struct node {
    struct data {
        int64 s;
        int mn;
        int64 lz;

        data() { s = lz = 0, mn = INF; }
        data(int x) : s(x), mn(x) { lz = 0; }
        data(int64 s, int mn) : s(s), mn(mn) { lz = 0; }

        data merge(const data &other) {
            return data(s + other.s, min(mn, other.mn));
        }
    };

    // range of node: [a, b]
    int a, b;
    // children
    int l, r;
    data d;

    node(int a, int b, int l = -1, int r = -1, data d = data())
        : a(a), b(b), l(l), r(r), d(d) {}
};

struct stree {
    vector<node> t;
    vector<int> v;

    stree(vector<int> v) : v(v) {}

    int new_node(node x) {
        t.push_back(x);
        return (int)t.size() - 1;
    }

    int build(int a, int b) {  // returns node created
        if (a == b) return new_node(node(a, b, -1, -1, node::data(v[a])));

        int m = (a + b) >> 1;

        int nl = build(a, m);
        int nr = build(m + 1, b);

        return new_node(node(a, b, nl, nr, t[nl].d.merge(t[nr].d)));
    }

    void push(int x) {
        if (!t[x].d.lz) return;

        t[x].d.s += 1LL * (t[x].b - t[x].a + 1) * t[x].d.lz;
        t[x].d.mn += t[x].d.lz;

        if (t[x].a != t[x].b) {
            t[t[x].l].d.lz += t[x].d.lz;
            t[t[x].r].d.lz += t[x].d.lz;
        }

        t[x].d.lz = 0;
    }

    void upd(int x, int a, int b, int v) {
        push(x);

        if (t[x].a > b || t[x].b < a) return;

        if (t[x].a >= a && t[x].b <= b) {
            t[x].d.lz = v;
            push(x);
            return;
        }

        upd(t[x].l, a, b, v);
        upd(t[x].r, a, b, v);

        t[x].d = t[t[x].l].d.merge(t[t[x].r].d);
    }

    node::data query(int x, int a, int b) {
        push(x);

        if (t[x].a > b || t[x].b < a) return node::data();

        if (t[x].a >= a && t[x].b <= b) return t[x].d;

        return query(t[x].l, a, b).merge(query(t[x].r, a, b));
    }
};

/*
Usage:
    stree st;
    int root = st.build(0, n - 1);

    // update
    st.upd(root, a, b, x);

    // query
    st.query(root, a, b);
*/
