/*
Segment Tree Data Structure

This is a template for segment tree. This shows an implementation of
- add in a range `x`
- tell sum in a range

So this one implements lazy.

Whole structure is 0-indexed use inclusive intervals [a, b].
*/

using int64 = long long;

struct node {
    int a, b;        //range of node: [a, b]
    int64 s, lazy;   //sum and lazy in this case
    int l, r;        //children

    node(int a, int b, int64 s = 0, int64 lazy = 0, int l = -1, int r = -1) :
        a(a), b(b), s(s), lazy(lazy), l(l), r(r) {}
};

template <typename T>
struct stree {
    vector <T> t;

    stree() {}

    int new_node(T x) {
        t.push_back(x);
        return (int) t.size() - 1;
    }

    int build(int a, int b) { // returns node created
        if(a == b)
            return new_node(T(a, b));

        int m = (a + b) >> 1;

        int nl = build(a, m);
        int nr = build(m + 1, b);

        return new_node(T(a, b, 0, 0, nl, nr));
    }

    void push(int x) {
        t[x].s += 1LL * (t[x].b - t[x].a + 1) * t[x].lazy;

        if(t[x].a != t[x].b) {
            t[t[x].l].lazy += t[x].lazy;
            t[t[x].r].lazy += t[x].lazy;
        }

        t[x].lazy = 0;
    }

    void upd(int x, int a, int b, int k) {
        push(x);

        if(t[x].a > b || t[x].b < a)
            return;

        if(t[x].a >= a && t[x].b <= b) {
            t[x].lazy = k;
            push(x);
            return;
        }

        upd(t[x].l, a, b, k);
        upd(t[x].r, a, b, k);

        t[x].s = t[t[x].l].s + t[t[x].r].s;
    }

    int64 query(int x, int a, int b) {
        push(x);

        if(t[x].a > b || t[x].b < a)
            return 0LL;

        if(t[x].a >= a && t[x].b <= b)
            return t[x].s;

        return query(t[x].l, a, b) + query(t[x].r, a, b);
    }
};

/*
Usage:
    stree <node> st;
    int root = st.build(0, n - 1);

    // update
    st.upd(root, a, b, x);

    // query
    st.query(root, a, b);
*/