
template<typename T>
vector<T> merge(const vector<T>& left, const vector<T>& right) {
	int n = int(left.size());
	int m = int(right.size());
	int i = 0, j = 0;
	vector<T> comb;
	while (i < n or j < m) {
		if (i < n and (j == m or left[i] < right[j]))
			comb.emplace_back(left[i++]);
		else
			comb.emplace_back(right[j++]);
	}
	return comb;
}

template<typename T>
void merge_sort(vector<T>& arr) {
	int n = int(arr.size());
	if (n == 1)
		return;
	int mid = n / 2;
	vector<T> left, right;
	for (int i = 0; i < mid; i++) left.emplace_back(arr[i]);
	for (int i = mid; i < n; i++) right.emplace_back(arr[i]);
	merge_sort(left);
	merge_sort(right);

	arr = merge(left, right);
}