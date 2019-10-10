//regla de simpson para integracion numerica
//tested on COJ 2121

const double EPS = 1e-10;

double compareDouble(double a, double b) {
	if(a < b - EPS)
		return -1;

	if(a > b + EPS)
		return 1;

	return 0;
}

double simpson(double (*f) (double), double a, double b) {
	return (f(a) + 4.0 * f((a + b) / 2.0) + f(b)) * (b - a) / 6.0;
}

double integrate(double (*f) (double), double a, double b) {
	//llamar aca para integrar, f debe ser una funcion f(x), x es double y regresa double
	//a y b son los limites de integracion

	double m = (a + b) / 2.0;
	double am = simpson(f, a, m);
	double mb = simpson(f, m, b);
	double ab = simpson(f, a, b);

	if(compareDouble(am + mb, ab) == 0)
		return ab;

	return integrate(f, a, m) + integrate(f, m, b);
}