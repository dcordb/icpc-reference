struct Fenwick { //1 indexed
    vector <int> ft;

    fenwick(int n) {
        ft.assign(n + 1, 0);
    }

    //possibly change apply
    void upd(int x, int v) {
        for(; x < (int) ft.size(); x += x & -x)
            ft[x] += v;
    }

    //possibly change here, return type and merge
    int query(int x) {
        int s = 0;
        for(; x > 0; x -= x & -x)
            s += ft[x];

        return s;
    }
};

/*
A Fenwick Tree implementation.
It needs to be 1 indexed.

Usage:
    Fenwick f(5);
    f.upd(..., ...)
    f.query(...)
*/