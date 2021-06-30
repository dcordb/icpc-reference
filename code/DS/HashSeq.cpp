//computes hashes of a sequence of integers
//0-indexed

struct HashItem {
	int B, MOD, INV;
	vector <int> pw, inv;

	HashItem(int B, int MOD, int INV) : B(B), MOD(MOD), INV(INV) {}

	void pre_pw(int n) {
		pw.assign(n, 0);
		inv.assign(n, 0);

		if(n > 0) {
			pw[0] = inv[0] = 1;
			for(int i = 1; i < n; i++) {
				pw[i] = 1LL * pw[i - 1] * B % MOD;
				inv[i] = 1LL * inv[i - 1] * INV % MOD;
			}
		}
	}
};

HashItem one(37, (int) 1e9 + 7, 621621626);
HashItem two(41, (int) 1e9 + 21, 292682933);

struct HashSeq {
	vector <HashItem> items;
	vector <vector <int> > seqs;

	HashSeq(vector <int> s, vector <HashItem> h_items) : items(h_items) {
		for(auto &item : items)
			item.pre_pw(s.size());

		seqs.assign(items.size(), vector <int> ());

		for(int k = 0; k < (int) items.size(); k++) {
			auto &cur_item = items[k];
			auto &cur_seq = seqs[k];

			cur_seq.assign(s.size(), 0);

			for(int i = 0; i < (int) s.size(); i++) {
				cur_seq[i] = 1LL * cur_item.pw[i] * s[i] % cur_item.MOD;

				if(i > 0)
					cur_seq[i] = (cur_seq[i - 1] + cur_seq[i]) % cur_item.MOD;
			}
		}
	}

	//[l, r]
	vector <int> get_hash(int l, int r) {
		/*
			computes 0-indexed hashes for all items from seq in range [l, r]
			l <= r
		*/

		assert(l <= r);
        assert(l >= 0 && r < seqs[0].size());

		vector <int> res(items.size(), 0);

		for(int i = 0; i < (int) items.size(); i++) {
			auto &cur_seq = seqs[i];
			auto &cur_item = items[i];

			int sum = cur_seq[r];

			if(l > 0)
				sum = (sum - cur_seq[l - 1] + cur_item.MOD) % cur_item.MOD;

			sum = 1LL * sum * cur_item.inv[l] % cur_item.MOD;
			res[i] = sum;
		}

		return res;
	}
};

/*
	Usage HashSeq(my_array, { one, two, ... })
*/
