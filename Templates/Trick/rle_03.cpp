template<typename T = int>
vector<T> rle_k_difference(vector<T>& arr, T difference, bool sortt = false) {
	if (arr.empty()) return {};
	vector<T> ans;
	if (sortt == true) if (!is_sorted(arr.begin(), arr.end())) sort(arr.begin(), arr.end());
	arr.emplace_back(numeric_limits<T>::max());
	int cnt = 1;
	for (int i = 0; i < int(arr.size()); i++) {
		if (arr[i + 1] - arr[i] <= difference) cnt++;
		else ans.emplace_back(cnt), cnt = 1;
	}
	return ans;
}