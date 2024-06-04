const int inf = int(1e9) + 10;
int tot_v = accumulate(value.begin(), value.end(), 0);
vector<intll> dp(tot_v + 1, inf);
dp[0] = 0;
for (int i = 0; i < n; i++) {
	for (int v = tot_v; v >= value[i]; v--)
		dp[v] = min(dp[v], dp[v - value[i]] + weight[i]);
}

for (int i = tot_v; i >= 0; i--) {
	if (k >= dp[i]) {
		cout << i << " ";
		break;
	}
}