/*
Basic Segment Tree
update on point
query sum

usage:
stree tree(a);
int root = tree.build(0, a.size() - 1);
 */

struct node {
    struct data {
        int64 s;

        data() { s = 0; }
        data(int64 s) : s(s) {}

        data merge(const data &other) { return data(s + other.s); }
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

    void upd(int x, int p, int v) {
        if (t[x].a > p || t[x].b < p) return;

        if (t[x].a == t[x].b) {
            t[x].d.s = v;
            return;
        }

        upd(t[x].l, p, v);
        upd(t[x].r, p, v);

        t[x].d = t[t[x].l].d.merge(t[t[x].r].d);
    }

    node::data query(int x, int a, int b) {
        if (t[x].a > b || t[x].b < a) return node::data();

        if (t[x].a >= a && t[x].b <= b) return t[x].d;

        return query(t[x].l, a, b).merge(query(t[x].r, a, b));
    }
};
