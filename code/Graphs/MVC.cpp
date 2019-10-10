//Minimum Vertex Cover (taken from Wikipedia) to use with Hopcroft Karp or Kuhn Matching
//this goes in the namespace of HK or kuhn
//remember that Maximum Independet Set is the complement of a MVC
//MVC is minimum number of nodes to cover all edges
//MIS is maximum number of nodes such that there are not two adjacents

vector <int> getVertexCover() { //remember call getMaxFlow first
	vector <int> lft, rgt;
	queue <int> q;

	for(int i = 1; i <= n; i++) {
		if(i <= l) {
			lft.push_back(i);

			if(left[i] == 0)
				q.push(i);
		}

		else rgt.push_back(i);
	}

	vector <int> mk(n + 1, 0);
	vector <int> z;

	while(!q.empty()) {
		int u = q.front();
		q.pop();

		if(u == 0 || mk[u])
			continue;

		mk[u] = 1;
		z.push_back(u);

		for(int v : g[u]) {
			if(left[u] == v)
				continue;

			if(!mk[v]) {
				mk[v] = 1;
				z.push_back(v);
				q.push(right[v]);
			}
		}
	}

	sort(z.begin(), z.end());

	vector <int> s1, s2, res;

	set_difference(lft.begin(), lft.end(), z.begin(), z.end(), inserter(s1, s1.begin()));
	set_intersection(rgt.begin(), rgt.end(), z.begin(), z.end(), inserter(s2, s2.begin()));
	set_union(s1.begin(), s1.end(), s2.begin(), s2.end(), inserter(res, res.begin()));

	return res;
}