struct CentDec {
    vector <vector <int>> g;
    vector <int> sz, cent;

	// graph and root to start doing the decomposition
    CentDec(const vector <vector <int>> &g, int root) : g(g) {
        sz.assign(g.size(), 0);
        cent.assign(g.size(), 0);

        cdec(root, -1);
    }

    void dfs2(int u, int pt) {
        sz[u] = 0;

        for(int v : g[u]) {
            if(v == pt || cent[v])
                continue;

            dfs2(v, u);
            sz[u] += sz[v];
        }

        sz[u]++;
    };

    int dfs1(int u, int r, int pt) {
        int t = -1;

        for(int v : g[u]) {
            if(v == pt || cent[v])
                continue;

            if(t == -1 || sz[v] > sz[t])
                t = v;
        }

        if(t == -1 || 2 * sz[t] <= sz[r])
            return u;

        return dfs1(t, r, u);
    };

    void cdec(int u, int p) {
        dfs2(u, -1);
        int c = dfs1(u, u, -1);

        solve(c);

        cent[c] = 1;  // mark as centroid
        
        for(int v : g[c])
            if(!cent[v])
                cdec(v, c);
    }

    void solve(int c) {
        /*
			solve for a centroid here.
			whatever you do, remember that you can't go to a node marked as a centroid.
		*/
    }
};

/*
Basic Centroid Decomposition.
A centroid is a node that its removal divides the tree in trees each having less than or equal to half of original tree's size.

It works for both 0 or 1 indexed.

Usage:
	CentDec cdec(g, 0); //this starts the centroid decomposition

Time Complexity: O(n log n) * O(solve)
*/