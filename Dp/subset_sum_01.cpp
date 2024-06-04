// N -> Maximum sum of the array
// TC : O(N * sqrt(N))
const int N = 1e5 + 1;
vector<int> freq(N + 1, 0);
vector<array<int, 2>> cmp;
for (int i = 1; i <= N; i++)
	if (freq[i])
		cmp.push_back({i, freq[i]});

bitset<N> dp;
dp[0] = 1;
for (auto &[w, k] : cmp) {
	bitset<N> newdp = dp;
	for (int p = 0; p < w; p++) {
		int S = 0;
		for (int mul = p, cnt = 0; mul <= N; mul += w, cnt++) {
			if (cnt > k) S -= dp[mul - w * cnt], cnt--;
			if (S > 0) newdp[mul] = 1;
			S += dp[mul];
		}
	}
	swap(dp, newdp);
}

int sub_sum = dp._Find_first();
while (dp._Find_next(sub_sum) != N) {
	sub_sum = dp._Find_next(sub_sum);
}