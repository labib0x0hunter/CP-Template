// cc = counter_clockwise
template <typename T = vector<int>>
vector<T> rotate90(int n, int m, vector<T>& Arr, bool cc = true) {
	vector<T> Brr(m, T(n, Arr[0][0]));
	if (cc) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				Brr[m - 1 - j][i] = Arr[i][j];
	}
	else {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				Brr[j][n - 1 - i] = Arr[i][j];
	}
	return Brr;
}