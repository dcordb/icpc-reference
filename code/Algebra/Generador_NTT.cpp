#include <bits/stdc++.h>
using namespace std;

typedef long long int64;

int64 exp(int64 a, int64 b, int MOD) {
	if(b == 0)
		return 1;

	if(b % 2 == 1)
		return a * exp(a, b - 1, MOD) % MOD;

	int64 sq = exp(a, b / 2, MOD);
	return sq * sq % MOD;
}

int main() {
	vector <int> f; //aqui poner los factores distintos de x * 2^(algo)
	f.push_back(2);
	f.push_back(11);

	int p = 786433; //poner el primo x * 2^(algo) + 1

	for(int i = 2;; i++) {
		int bad = 0;
		for(int o : f) {
			int64 r = exp(i, (p - 1) / o, p);

			if(r == 1)
				bad = 1;
		}

		if(!bad) {
			printf("gen %d\n", i); //i es generador
			return 0;
		}
	}

	return 0;
}