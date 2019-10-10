struct node { //struct de nodo de segment tree
	int v, left, right;
	
	node(int v, int left, int right) : v(v), left(left), right(right) {}
};

//IMPORTANTE: siempre recordar annadir null al stree, osea hacer stree.push_back(null)
node null(0, 0, 0);
vector <node> stree;

int root[MAX]; //arreglos de raices

int build(int st, int nd) {
	if(st == nd) {
		stree.push_back(node(a[st], 0, 0));
		return (int) stree.size() - 1;
	}

	int mid = (st + nd) >> 1;

	int left = build(st, mid);
	int right = build(mid + 1, nd);

	stree.push_back(node(0, left, right)); //combino como haga falta
	return (int) stree.size() - 1;
}

int insert(int x, int st, int nd, int p, int v) {
	if(st > p || nd < p)
		return x; //si .. tengo q regresar x
		
	if(st == nd) {
		stree.push_back(node(v, 0, 0));
		return (int) stree.size() - 1;
	}

	int mid = (st + nd) >> 1;
	
	int left = insert(stree[x].left, st, mid, p, v);
	int right = insert(stree[x].right, mid + 1, nd, p, v);
	
	stree.push_back(node(stree[left].v + stree[right].v, left, right)); //combino como haga falta, esto es un ejemplo
	return (int) stree.size() - 1;
}

int query(int x, int st, int nd, int p) { //query .. casi igual q un stree normal
	if(st > p || nd < p)
		return -1;
		
	if(st == nd)
		return stree[x].v;
		
	int mid = (st + nd) >> 1;
	
	int left = query(stree[x].left, st, mid, p);
	int right = query(stree[x].right, mid + 1, nd, p);
	
	return max(left, right);
}