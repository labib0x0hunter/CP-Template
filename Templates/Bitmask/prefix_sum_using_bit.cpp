vector<vector<int>> prefixx_bit(n + 1, vector<int>(32, 0));
for (int i = 1; i <= n; i++) {
	for (int j = 0; j < 32; j++) {
		prefixx_bit[i][j] = prefixx_bit[i - 1][j] + ((arr[i - 1] >> j) & 1);
	}
}

int ans = 0;
int l = min(n, 2), r = min(n, 5);
for (int j = 0; j < 32; j++) {
	int cnt_one = prefixx_bit[r][j] - prefixx_bit[l][j];
	ans += (cnt_one * (1 << j));
}