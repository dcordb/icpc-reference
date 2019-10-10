//O(min(n, m) * n * m)

const int
	MAXN = 305, //equations
	MAXM = 305, //variables
	INF = 1e9;
const double eps = 1e-9;
int n;
double p, ans[MAXM], a[MAXN][MAXM]; //1-indexed

//a[i][j] is the coefficient of jth variable of the ith equation
//if j is last columnn then it is the constant of equation
//ans[j] is the result of jth variable

//also returns the number of solutions (0, 1 or infinity)

//equations, variables (without counting last column), augmented matrix, answer
int gauss(int n, int m, double a[MAXN][MAXM], double ans[MAXM]) {
	int pos[MAXM];
	memset(pos, 0, sizeof(pos));

	bool flag = 0;
	int row = 1, col = 1;

	for(; row <= n && col <= m; col++) {
		int piv = row;

		for(int i = row; i <= n; i++)
			if(fabs(a[i][col]) > fabs(a[piv][col]))
				piv = i;

		if(fabs(a[piv][col]) < eps) {
			flag = 1;
			continue;
		}

		for(int i = 1; i <= m + 1; i++)
			swap(a[row][i], a[piv][i]);

		pos[col] = row;

		double d = a[row][col];
		for(int i = 1; i <= m + 1; i++)
			a[row][i] /= d;

		for(int i = 1; i <= n; i++) {
			if(i == row)
				continue;

			d = a[i][col];
			for(int j = 1; j <= m + 1; j++)
				a[i][j] -= a[row][j] * d;
		}

		row++;
	}

	for(int i = 1; i <= m; i++) {
		if(pos[i] == 0)
			ans[i] = 0;

		else ans[i] = a[pos[i]][m + 1];
	}

	for(int i = 1; i <= n; i++) {
		double sum = 0;
		for(int j = 1; j <= m; j++)
			sum += ans[j] * a[i][j];

		if(fabs(sum - a[i][m + 1]) > eps)
			return 0;
	}

	if(flag)
		return INF;

	return 1;
}