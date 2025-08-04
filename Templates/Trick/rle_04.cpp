// blocks are accending order
// arr.emplace_back(maxx); for decending order
template<typename T = int>
vector<T> rle_sorted_blocks(vector<T> arr) {
	if (arr.empty()) return {};
	vector<T> ans;
	int n = arr.size();
	arr.emplace_back(-1);
	int cnt = 1;
	for (int i = 0; i < n; i++) {
		if (arr[i + 1] >= arr[i]) cnt++;
		else ans.emplace_back(cnt), cnt = 1;
	}
	return move(ans);
}