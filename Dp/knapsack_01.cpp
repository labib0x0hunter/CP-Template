int tot_weight = accumulate(weight.begin(), weight.end(), 0ll) + k;
// dp[w] = maximum value canbe taken with weight w
vector<intll> dp(tot_weight + 1, 0);
for (int i = 0; i < n; i++) {
	for (int w = k; w >= weight[i]; w--) {
		intll take_n = dp[w - weight[i]] + values[i];
		dp[w] = max(dp[w], take_n);
	}
}