vector<intll> prefix_summ(vector<int>& arr) {
	int n = arr.size();
	vector<intll> summ(n + 1);
	summ[1] = arr[0];
	for (int i = 1; i < n; i++)
		summ[i + 1] = summ[i] + (intll) arr[i];
	return move(summ);
}