//ternary search for minimum (for maximum reverse < operator)

double st = -INF, nd = INF; //domain of function
for(int i = 1; i <= 150; i++) {
	double m1 = st + (nd - st) / 3.0;
	double m2 = nd - (nd - st) / 3.0;

	if(f(m1) < f(m2))
		nd = m2;

	else st = m1;
}

double res = (st + nd) / 2.0; //optimal point