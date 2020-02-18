//Basis in Z_2, vectors are binary numbers

struct basis {
	int t;
	vector <int> v;

	basis(int t_) {
		t = t_;
		v.assign(t, 0);
	}

	/*
		returns boolean that denotes whether k was generated or not by basis
		true is generated, false is not generated
	*/
	bool add_vector(int k) {
		for(int i = t - 1; i >= 0; i--) {
			if(k >> i & 1) {
				if(v[i] == 0) {
					v[i] = k;
					break;
				}

				else k ^= v[i];
			}
		}

		return !k ? true : false;
	}
};