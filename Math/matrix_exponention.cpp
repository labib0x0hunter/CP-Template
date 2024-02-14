#include<bits/stdc++.h>
using namespace std;

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

int32_t main() {

	ios::sync_with_stdio(false) ; cin.tie(0) ;

	long long a, x, m;
	cin >> a >> x >> m;

	auto ans = mat_expo<long long>(vector<vector<long long>> {{a, 1}, {0, 1}}, x, m);
	cout << ans[0][1] << endl;

	return 0;
}

// https://atcoder.jp/contests/abc293/tasks/abc293_e