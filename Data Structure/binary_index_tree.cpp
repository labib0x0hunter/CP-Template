template<typename T = int>
struct binary_index_tree {
#define LSONE(x) ((x) & -(x))

	int N;
	vector<T> t;

	binary_index_tree() {}
	binary_index_tree(int n) : N(n) {
		t.resize(N + 1);
	}
	binary_index_tree(vector<int>& arr) {
		N = int(arr.size());
		t.resize(N + 1);

		for (int i = 1; i <= N; i++)
			update(i, arr[i - 1]);
	}

	void update(int i, T x) {
		while (i <= N) {
			t[i] += x;
			i += LSONE(i);
		}
	}

	T query(int i) {
		T summ = 0;
		while (i > 0) {
			summ += t[i];
			i -= LSONE(i);
		}
		return summ;
	}

	void range_update(int l, int r, T x) {
		update(l, x);
		update(r + 1, -x);
	}

	// Find first index x such that summ(x) >= s
	int find_first(T s) {
		// Find last index x such that summ(x) < s
		int index = 0;
		int k = 0;

		while (1 << (k + 1) <= N)
			k++;
		while (k >= 0) {
			int next_index = index + (1 << k);
			if (next_index <= N and t[next_index] < s) {
				index = next_index;
				s -= t[index];
			}
			k--;
		}
		return index + 1;
	}
};

// Range Update Range Query
// Add to every element
template<typename T = int>
struct RURQ {

	binary_index_tree<T> rupq, purq;
	RURQ() {}
	RURQ(int m) {
		rupq = binary_index_tree<T>(m);
		purq = binary_index_tree<T>(m);
	}
	RURQ(vector<int>& arr) {
		rupq = binary_index_tree<T>(int(arr.size()));
		purq = binary_index_tree<T>(int(arr.size()));
		for (int i = 1; i <= int(arr.size()); i++)
			range_update(i, i, arr[i - 1]);
	}

	void range_update(int i, int j, T x) {
		rupq.range_update(i, j, x);
		purq.update(i, 1ll * x * (i - 1));
		purq.update(j + 1, -1ll * x * j);
	}

	// Range Query
	T query(int i) {
		return 1ll * rupq.query(i) * i - purq.query(i);
	}
};