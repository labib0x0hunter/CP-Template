template<typename T = int>
vector<pair<T, int>> rle_vector_frequency(vector<T>& arr) {
	if (arr.empty()) return {};
	vector<pair<T, int>> ans;
	T c = arr[0];
	int n = 1;
	for (int i = 1; i < (int)arr.size(); i++) {
		if (arr[i] == c) n++;
		else {
			ans.emplace_back(c, n);
			c = arr[i], n = 1;
		}
	}
	ans.emplace_back(c, n);
	return ans;
}