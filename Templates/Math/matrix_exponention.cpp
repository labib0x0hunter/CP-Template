template<typename T = int>
using MATRIX = vector<vector<T>>;

template<typename T = int>
MATRIX<T> mat_mul(MATRIX<T> a, MATRIX<T> b, T mod) {
	int n = a.size();
	MATRIX<T> ans(n, vector<T>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++) {
				ans[i][j] += (1ll * a[i][k] * b[k][j]) % mod;
				ans[i][j] %= mod;
			}
	return ans;
}

template<typename T = int>
MATRIX<T> mat_expo(MATRIX<T> a, T b, T mod) {
	int n = a.size();
	MATRIX<T> ans(n, vector<T>(n));
	for (int i = 0; i < n; i++) ans[i][i] = 1;
	while (b) {
		if (b & 1) ans = mat_mul<T>(ans, a, mod);
		a = mat_mul<T>(a, a, mod);
		b >>= 1;
	}
	return ans;
}

// f0 = 0, f1 = 1
int nth_fibonacci(int n, int f0, int f1, int mod) {
	MATRIX<int> mat{{1, 1}, {1, 0}};
	mat = mat_expo<int>(mat, n, mod);
	return ((1ll * mat[1][0] * f1) % mod + (1ll * mat[1][1] * f0) % mod) % mod;
}