// arr[i] <= x, last index of i
int last_find(vector<int>& arr, int x) {
	auto it = upper_bound(arr.begin(), arr.end(), x);
	if (it == arr.begin()) return -1;
	--it;
	return it - arr.begin();
}

// arr[i] <= x, first index of i
int first_find(vector<int>& arr, int x) {
	auto it = lower_bound(arr.begin(), arr.end(), x);
	if (it == arr.end()) return -1;
	if (*it == x) return it - arr.begin();
	if (it == arr.begin()) return -1;
	--it;
	return (*it <= x ? it - arr.begin() : -1);
}