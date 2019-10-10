/*
Given a tree, its LCA structure, discovery time and finish time
Computes a compressed tree of vertices of v, having the same structure
as the original tree.

All of this in O(k log k) if there are k vertices in v.

1-indexed everywhere (except vector v)
*/

struct CompressedTree {
	vector <vector <pair <int, int> > > g;
	vector <int> orig_id;
	int root;

	CompressedTree(vector <int> v, LCA &lca, const vector <int> &td, const vector <int> &tf) {
		sort(v.begin(), v.end(), [&] (int a, int b) { return td[a] > td[b]; });

		int m = v.size();
		for(int i = 1; i < m; i++) {
			int l = lca.lca(v[i - 1], v[i]);
			v.push_back(l);
		}

		sort(v.begin(), v.end());
		auto it = unique(v.begin(), v.end());
		v.erase(it, v.end());

		sort(v.begin(), v.end(), [&] (int a, int b) { return td[a] > td[b]; });

		stack <int> st;

		g.assign(v.size() + 1, {});
		orig_id.assign(v.size() + 1, 0);

		int id = 0;
		for(int x : v) {
			orig_id[++id] = x;

			while(!st.empty() && td[orig_id[st.top()]] >= td[x] && td[orig_id[st.top()]] <= tf[x]) {
				int u = orig_id[st.top()];
				g[id].push_back({st.top(), lca.l[u] - lca.l[x]}); //also saving distance between nodes
				st.pop();
			}

			st.push(id);
		}

		g[0].push_back({st.top(), lca.l[orig_id[st.top()]]});
		root = 0; //0 is root of the tree
	}
};