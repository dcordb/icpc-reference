#include <bits/stdc++.h>
using namespace std;

namespace fft { //si da problemas de precision se puede reemplazar double por long double lo q es mas lento
	typedef int T; //tipo de los coeficientes
	typedef complex <double> cpx;
	const int MAX = (1 << 20) + 1; //mayor estricto q el doble del maximo grado
	const double pi = acos(-1.0);
	int rev[MAX];
	cpx wlen_pw[MAX], fa[MAX], fb[MAX];

	void fft(cpx a[], int n, bool inv) {
		for(int i = 0; i < n; i++)
			if(i < rev[i])
				swap(a[i], a[rev[i]]);

		for(int len = 2; len <= n; len <<= 1) {
			double ang = 2 * pi / len * (inv ? -1 : 1);
			int len2 = len >> 1;

			cpx wlen(cos(ang), sin(ang));
			wlen_pw[0] = cpx(1, 0);

			for(int i = 1; i < len2; i++)
				wlen_pw[i] = wlen_pw[i - 1] * wlen;

			for(int i = 0; i < n; i += len) {
				cpx t,
					*pu = a + i,
					*pv = a + i + len2,
					*pu_end = a + i + len2,
					*pw = wlen_pw;

				for(; pu != pu_end; pu++, pv++, pw++) {
					t = *pv * *pw;
					*pv = *pu - t;
					*pu += t;
				}
			}
		}

		if(inv) {
			for(int i = 0; i < n; i++)
				a[i] /= n;
		}
	}

	void calc_rev(int n, int lg) {
		for(int i = 0; i < n; i++) {
			rev[i] = 0;

			for(int j = 0; j < lg; j++) {
				if(i & (1 << j))
					rev[i] |= 1 << (lg - 1 - j);
			}
		}
	}

	void multiply(int la, T a[], int lb, T b[]) {
		int n = 1, l = 0;
		int lim = 2 * max(la, lb);

		while(n < lim) {
			n *= 2;
			l++;
		}

		calc_rev(n, l);

		for(int i = 0; i < n; i++) {
			if(i < la)
				fa[i] = cpx(a[i], 0);

			else fa[i] = cpx(0, 0);
		}

		for(int i = 0; i < n; i++) {
			if(i < lb)
				fb[i] = cpx(b[i], 0);

			else fb[i] = cpx(0, 0);
		}

		fft(fa, n, false); fft(fb, n, false);

		for(int i = 0; i < n; i++)
			fa[i] = fa[i] * fb[i];

		fft(fa, n, true);

		for(int i = 0; i < n; i++)
			a[i] = (T) (fa[i].real() + 0.5);
	}
}

int x[fft::MAX], y[fft::MAX]; //ojo vectores auxiliares tienen q tener tamanno de poly de fft