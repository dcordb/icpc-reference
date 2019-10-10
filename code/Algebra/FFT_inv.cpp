//usar con NTT, de hacer falta se puede hacer tambien con FFT lo que hay que modulear aparte en el FFT

int r[ntt::MAX], x[ntt::MAX], y[ntt::MAX];

void poly_inv(int n, int p[]) { //size and polynomial
	if(p[0] == 0) //inverse doesnt exist
		return;

	int inv = exp(p[0], ntt::MOD - 2); //find modular inverse of p[0]

	for(int i = 0; i < n; i++) //multiply polynomial by inverse such that p[0] = 1
		p[i] = 1LL * p[i] * inv % ntt::MOD;

	r[0] = 1;

	for(int i = 1; i <= m; i <<= 1) { //cantidad de terminos que hacen falta, en este caso m
		for(int j = 0; j < i; j++)
			x[j] = y[j] = r[j];

		ntt::multiply(i, x, i, y);

		for(int j = 0; j < n; j++)
			y[j] = p[j];

		ntt::multiply(2 * i - 1, x, n, y);

		for(int j = 0; j < i; j++) {
			r[j] *= 2;
			r[j] %= ntt::MOD;
		}

		for(int j = 0; j < 2 * i; j++) {
			r[j] -= x[j];
			r[j] %= ntt::MOD;
			r[j] = (r[j] + ntt::MOD) % ntt::MOD;
		}
	}

	for(int i = 0; i < m; i++)
		r[i] = 1LL * r[i] * inv % ntt::MOD; //inverso
}