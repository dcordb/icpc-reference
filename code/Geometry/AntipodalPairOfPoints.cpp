vector <pair <pt, pt> > antipodal(vector <pt> &r) { //recibe como parametro el poligono convexo
	vector <pair <pt, pt> > ans;
	int k = 1;
	int m = r.size();

	while(k < m - 1 && llabs(cross(r[k + 1] - r[m - 1], r[0] - r[m - 1])) > llabs(cross(r[k] - r[m - 1], r[0] - r[m - 1])))
		k++;

	int j = k;

	for(int i = 0; i <= k && j < m; i++) {
		ans.push_back({r[i], r[j]});

		while(j < m - 1 && llabs(cross(r[j + 1] - r[i], r[i + 1] - r[i])) > llabs(cross(r[j] - r[i], r[i + 1] - r[i]))) {
			j++;
			ans.push_back({r[i], r[j]});
		}
	}

	return ans;
}