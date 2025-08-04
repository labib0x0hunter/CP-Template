// dp[i] = minimum element of the last element in LIS of length i + 1
// lis_rank[i] = lis until i,
// lis = max(lis_rank)
template<typename T = int, bool strong = true>
vector<T> LIS(vector<T> arr) {
	int n = int(arr.size());
	vector<T> dp(n, numeric_limits<T>::max());
	vector<int> lis_rank(n);
	for (int i = 0; i < n; i++) {
		int j = (strong ?
		         distance(dp.begin(), lower_bound(dp.begin(), dp.end(), arr[i])) :
		         distance(dp.begin(), upper_bound(dp.begin(), dp.end(), arr[i]))
		        );
		dp[j] = arr[i];
		lis_rank[i] = j + 1;
	}
	return move(lis_rank);
}

// {lis_arr, lis_index}
template<typename T = int>
vector<pair<T, int>> restoreLIS(vector<T>& arr, vector<int>& lis_rank, int lis_length) {
	int n = int(arr.size());
	vector<pair<T, int>> lis;
	for (int i = n - 1; i >= 0 && lis_length > 0; i--) {
		if (lis_rank[i] == lis_length) {
			lis.emplace_back(arr[i], i);
			lis_length--;
		}
	}
	reverse(lis.begin(), lis.end());
	return move(lis);
}