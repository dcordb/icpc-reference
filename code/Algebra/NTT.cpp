#include <bits/stdc++.h>
using namespace std;

/*
Modulo tiene que ser p = q * 2^c + 1, donde q es un natural y p es primo

Como buscar un generador:

Let p=2^32-2^20+1. Then p is of the form k*n+1,
that is needed for doing number theoretic transforms
upto length n=2^20. The factorization of p-1 is
p-1=2^20*3^2*5*7*13.

Now start testing numbers a=2, 3, 5, 7,... and see if
a^((p-1)/2) != 1 (mod p)
a^((p-1)/3) != 1 (mod p)
a^((p-1)/5) != 1 (mod p)
a^((p-1)/7) != 1 (mod p)
a^((p-1)/13) != 1 (mod p)
(the first a for which this should occur is a=19).
*/

//Lista de modulos con sus generadores

// p                   | deg | g
// 469762049             26    3
// 998244353             23    3
// 1107296257            24    10
// 10000093151233        26    5
// 1000000523862017      26    3
// 1000000000949747713   26    2
// 5767169               19    3
// 7340033               20    3

//Multiplicacion de numeros grandes (SPOJ VFMUL)

namespace ntt {
	const int P = 20; //1 << P mayor estricto q 2 * (grado maximo de polinomio), ademas 1 << P (q es el maximo valor de N) tiene q dividir a MOD - 1
	const int MAX = (1 << P) + 1; //se suma uno porque N puede ser exactamente 1 << P donde se forrearia por eso se le pone (1 << P) + 1
	const int GEN = 3;
	const int MOD = 7340033;

	int N;
	int w[MAX];

	int exp(int a, int b) {
		if(b == 0)
			return 1;

		if(b % 2 == 1)
			return 1LL * a * exp(a, b - 1) % MOD;

		int sq = exp(a, b / 2);
		return 1LL * sq * sq % MOD;
	}

	void NTT(int a[], int x[], int k, int v) {
		//K is the length of x[]
	  	//v=0 : DFT,  v=1 : IDFT

		w[0] = 1;

		int G = exp(GEN, (MOD - 1) / k);

		for(int i = 1; i <= k; i++)
			w[i] = 1LL * w[i - 1] * G % MOD;

		for(int i = 0, j = 0; i < k; i++) {
			if(i > j)
				swap(x[i], x[j]);

			for(int l = k >> 1; (j ^= l) < l; l >>= 1); //es j ^= l (la letra l) no un 1
		}

		for(int i = 2; i <= k; i <<= 1) {
			int mid = i >> 1;

			for(int j = 0; j < k; j += i) {
				for(int l = 0; l < mid; l++) {
					int t;

					if(v == 0)
						t = 1LL * x[j + l + mid] * w[(k / i) * l] % MOD;

					else t = 1LL * x[j + l + mid] * w[k - (k / i) * l] % MOD;

					x[j + l + mid] = (x[j + l] - t + MOD) % MOD;
					x[j + l] += t;
					x[j + l] %= MOD;
				}
			}
		}

		if(v == 1) {
			int r = exp(N, MOD - 2);

			for(int i = 0; i < N; i++)
				a[i] = 1LL * a[i] * r % MOD;
		}
	}

	//0-indexed
	void multiply(int la, int a[], int lb, int b[]) {
		/*OJO, el resultado se guarda en a. Cuando el algoritmo termina b se queda con valores
		del IDFT, por lo tanto si se quiere multiplicar de nuevo hay q resetearlo*/

		N = 1;
		int lim = 2 * max(la, lb);

		while(N < lim)
			N *= 2;

		for(int i = la; i < N; i++)
			a[i] = 0;

		for(int i = lb; i < N; i++)
			b[i] = 0;

		NTT(a, a, N, 0); NTT(a, b, N, 0);

		for(int i = 0; i < N; i++)
			a[i] = 1LL * a[i] * b[i] % MOD;

		NTT(a, a, N, 1);
	}
}

int x[ntt::MAX], y[ntt::MAX]; //ojo vectores auxiliares tienen q tener tamanno de poly de fft