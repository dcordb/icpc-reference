/*
    Euler Path or Cycle (Hierholzer’s Algorithm)
    Complexity: O(n + m)

    Undirected graphs:
        euler path exists iff there are exactly two vertices with odd degree
        euler cycle exists iff all vertices have even degree

        ignore nodes that have degree = 0

    Directed graphs:
        euler path exists iff there are exactly two vertices with
            |in_degree - out_degree| = 1

        euler cycle exists iff all vertices have in_degree = out_degree

        Ignore nodes that have in_degree = out_degree = 0

    Tested on:
        https://codeforces.com/contest/1152/problem/E (undirected)
        https://codeforces.com/contest/508/problem/D (directed)
        https://codeforces.com/contest/723/problem/E (undirected)
*/


// 0 indexed everywhere

enum GRAPH { DIRECTED, UNDIRECTED };

template <GRAPH type> 
vector<int> euler_path(const vector<vector<pair<int, int>>> &G)
{
	int n = G.size(), m = 0;
	for (int i = 0; i < n; ++i)
		m += G[i].size();

	bool can = false;
	int s = 0;

	if (type == UNDIRECTED) {
		m /= 2;

		//s no puede ser nodo suelto
		for (int i = 0; i < n; i++)
			if (!G[i].empty())
				s = i;

		int odd = 0;
		for (int i = 0; i < n; i++) {
			if (G[i].size() & 1)
				s = i, odd++;
		}

		can = odd == 0 || odd == 2;
	}

	else {
		vector <int> in_deg(n);
		for (int i = 0; i < n; i++)
			for (auto o : G[i])
				in_deg[o.first]++;

		//s no puede ser un nodo suelto
		for (int i = 0; i < n; i++)
			if (in_deg[i] > 0 || G[i].size() > 0)
				s = i;

		int st = 0, nd = 0, odd = n;

		for (int i = 0; i < n; i++) {
			int d = G[i].size() - in_deg[i];

			if (d == 1)
				s = i, st++;

			else if (d == -1)
				nd++;

			else if (d == 0)
				odd--;
		}

		can = odd == 0 || (odd == 2 && st == 1 && nd == 1);
	}

	if(!can) return {};

	vector<int> path;
	vector<int> pos(n);
	vector<bool> mark(m);

	function<void(int)> visit = [&](int u)
	{
		for (int v, id; pos[u] < G[u].size(); )
		{
			tie(v, id) = G[u][pos[u]++];
			if (!mark[id])
			{
				mark[id] = true;
				visit(v);
			}
		}
		path.push_back(u);
	};

	visit(s);
	reverse(path.begin(), path.end());
	if (path.size() != m + 1) path.clear();

	return path;
}

/*
    Usage:
        undirected graphs:
            euler_path<UNDIRECTED>(g)
        directed graphs:
            euler_path<DIRECTED>(g)
*/