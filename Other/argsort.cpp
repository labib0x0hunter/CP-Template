template<typename T = int>
vector<int> argsort(const vector<T> &arr) {
	int n = int(arr.size());
	vector<int> ids(n);
	iota(ids.begin(), ids.end(), 0);
	sort(ids.begin(), ids.end(), [&](int i, int j) {
		return (arr[i] == arr[j] ? i < j : arr[i] < arr[j]);
	});
	return move(ids);
}

template<typename T = int>
vector<int> rearrange(vector<T> &arr, vector<T>& idx) {
	vector<int> brr(int(arr.size()));
	for (int i = 0; i < int(arr.size()); i++)
		brr[i] = arr[idx[i]];
	return move(brr);
}