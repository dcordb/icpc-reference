/*
Gauss Elimination Algorithm on Z2 (ie. sum is xor, multiplication is and)
*/

template <typename T>
int gauss(vector<vector<T>> a, vector<T> &ans)
{
	int n = (int) a.size();
	int m = (int) a[0].size() - 1;

	vector<int> where(m, -1);
	for (int col = 0, row = 0; col < m && row < n; ++col)
	{
		int sel = row;
		for (int i = row; i < n; ++i)
			if (a[i][col] > a[sel][col])
				sel = i;
		if (a[sel][col] == 0)
			continue;
		for (int i = col; i <= m; ++i)
			swap(a[sel][i], a[row][i]);
		
        where[col] = row;
		for (int i = 0; i < n; ++i)
			if (i != row)
			{
				int c = a[i][col];
				for (int j = col; j <= m; ++j)
					a[i][j] ^= a[row][j] & c;
			}

		++row;
	}

	ans.assign(m, 0);

	for (int i = 0; i < m; ++i)
		if (where[i] != -1)
			ans[i] = a[where[i]][m];

	for (int i = 0; i < n; ++i)
	{
		int sum = 0;
		for (int j = 0; j < m; ++j)
			sum ^= ans[j] & a[i][j];
		if ((sum ^ a[i][m]) > 0)
			return 0;
	}

	for (int i = 0; i < m; ++i)
		if (where[i] == -1)
			return (int) (1e9);
	return 1;
}

/*
Usage
    vector <int> ans;
    gauss <int> (matrix, ans)

    NOTE: the matrix is the augmented matrix (ie. with one more column for constant equalities). 

Returns:
    number of solutions: 0, 1 or infinity.
*/