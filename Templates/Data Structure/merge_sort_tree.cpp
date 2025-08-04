struct merge_sort_tree {

	int N;
	vector<vector<int>> t;

	merge_sort_tree(vector<int>& arr) {
		N = int(arr.size());
		t.resize(4 * (N + 1));
		build(1, 1, N, arr);
	}

	void build(int n, int b, int e, vector<int>& arr) {
		if (b == e) {
			t[n].push_back(arr[b - 1]);
			return;
		}
		int mid = b + (e - b) / 2;
		build(2 * n, b, mid, arr);
		build(2 * n + 1, mid + 1, e, arr);
		merge(t[2 * n].begin(), t[2 * n].end(), t[2 * n + 1].begin(), t[2 * n + 1].end(), back_inserter(t[n]));
		return;
	}

	// count ai > X
	int query(int n, int b, int e, int i, int j, int k) {
		if (i > e || j < b) return 0;
		if (i <= b && e <= j)
			return t[n].end() - upper_bound(t[n].begin(), t[n].end(), k);
		int mid = (b + e) / 2;
		int L = query(2 * n, b, mid, i, j, k);
		int R = query(2 * n + 1, mid + 1, e, i, j, k);
		return L + R;
	}

	int query(int l, int r, int k) {
		return query(1, 1, N, l, r, k);
	}
};