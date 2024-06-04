template<typename T>
intll kadanas(vector<T>& arr) {
	intll summ = 0, ans = 0;
	for (int i = 0; i < int(arr.size()); i++) {
		summ = max(0ll, summ + arr[i]); // change here for non empty
		ans = max(ans, summ);
	}
	return ans;
}