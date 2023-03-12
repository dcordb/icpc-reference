struct DSU {
    vector<int> p, sz;

    DSU(int n) {
        p.assign(n, 0);
        sz.assign(n, 0);

        for (int i = 0; i < n; i++) p[i] = i, sz[i] = 1;
    }

    int findst(int x) { return p[x] = (x == p[x]) ? x : findst(p[x]); }

    bool joinst(int a, int b) {
        // returns whether it could join a, b

        a = findst(a);
        b = findst(b);

        if (a == b) return false;

        if (sz[a] < sz[b]) swap(a, b);

        sz[a] += sz[b];
        p[b] = a;

        return true;
    }
};
