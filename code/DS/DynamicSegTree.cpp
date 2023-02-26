/*
 A dynamic segment tree implementation, this means that leaves can be of any
 value.
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

    stree(int a, int b) { new_node(node(a, b)); }

    int new_node(node x) {
        t.push_back(x);
        return (int)t.size() - 1;
    }

    void upd(int x, int p, int v) {
        if (t[x].a > p || t[x].b < p) return;

        if (t[x].a == t[x].b) {
            t[x].d.s += v;
            return;
        }

        int mid = (t[x].a + t[x].b) >> 1;

        if (t[x].l == -1) t[x].l = new_node(node(t[x].a, mid));
        if (t[x].r == -1) t[x].r = new_node(node(mid + 1, t[x].b));

        upd(t[x].l, p, v);
        upd(t[x].r, p, v);

        t[x].d = t[t[x].l].d.merge(t[t[x].r].d);
    }

    int query(int x, int k) {  // this finds k-th minimum value
        if (t[x].a == t[x].b) return t[x].a;

        int l = t[x].l, r = t[x].r;

        if (l != -1 && t[l].d.s < k) return query(r, k - t[l].d.s);
        return query(l, k);
    }
};
