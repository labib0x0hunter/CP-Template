template<typename T = int>
struct sparse_table {

	int N;
	int log_N;

	vector<vector<T>> t;

	sparse_table() {}
	sparse_table(int n) : N(n) {
		log_N = log2(N) + 1;
		t.resize(N + 1, vector<T> (log_N, -1));
	}
	sparse_table(vector<int> &arr) {
		N = int(arr.size());
		log_N = log2(N) + 1;
		t.resize(N + 1, vector<T> (log_N, -1));
		build(arr);
	}

	void build(vector<int>& a) {
		for (int i = 1; i <= N; ++i)
			t[i][0] = a[i - 1];            // assignment
		for (int k = 1; (1 << k) <= N; ++k) {
			for (int i = 1; i + (1 << k) - 1 <= N; ++i)
				t[i][k] = max(t[i][k - 1], t[i + (1 << (k - 1))][k - 1]); // operation
		}
	}

	T query(int l, int r) {
		// assert(1 <= l and r <= N);
		int k = log2(r - l + 1);
		return max(t[l][k], t[r - (1 << k) + 1][k]); // operation
	}
};