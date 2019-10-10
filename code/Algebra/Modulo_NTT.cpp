#include <bits/stdc++.h>
using namespace std;

bool prime(int n) {
	for(int i = 2; i * i <= n; i++)
		if(n % i == 0)
			return 0;

	return 1;
}

int main() {
	int pw = 1 << 19; //poner 2^(algo) q se quiera

	for(int i = 3;; i++) {
		if(prime(pw * i + 1)) {
			printf("%d : %d\n", i, pw * i + 1); //el modulo es el 2do numero
			return 0;
		}
	}

	return 0;
}