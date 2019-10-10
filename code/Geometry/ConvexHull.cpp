struct pt {
	int x, y, id;
	
	pt(int x_ = 0, int y_ = 0, int id_ = 0) {
		x = x_, y = y_, id = id_;
	}
	
	bool operator < (const pt &p) const {
		if(y != p.y)
			return y < p.y;
		return x < p.x;
	}
	
	pt operator - (const pt &p) const {
		return pt(x - p.x, y - p.y, id);
	}
};

int cross(pt a, pt b) {
	return a.x * b.y - a.y * b.x;	
}

vector <pt> p;

vector <pt> convexHull(vector <pt> &p) {
	sort(p.begin(), p.end());
	
	int n = p.size();
	vector <pt> h(2 * n);
	
	int k = 0;
	for(int i = 0; i < n; i++) {
		while(k >= 2 && cross(h[k - 1] - h[k - 2], p[i] - h[k - 2]) <= 0)
			k--;
		h[k++] = p[i];
	}
	
	for(int i = n - 2, t = k + 1; i >= 0; i--) {
		while(k >= t && cross(h[k - 1] - h[k - 2], p[i] - h[k - 2]) <= 0)
			k--;
		h[k++] = p[i];
	}
	
	h.resize(k - 1);
	return h;
}