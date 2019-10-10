const double EPS = 1e-9; //poner epsilon q sea necesario

int CompareDouble(double a, double b) {
	if(a < b - EPS) //a menor q b
		return -1;

	if(a > b + EPS) //a mayor q b
		return 1;

	return 0; //a igual a b
}