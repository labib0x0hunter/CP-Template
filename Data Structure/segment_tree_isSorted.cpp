// Check if range [l, r] is sorted in accending order
struct node {
	using T = int;
	bool SORT;
	T minn, maxx;
};

template<typename T = node>
struct segment_tree {
	using TT = typename node::T;

	int N;
	vector<T> t;

	segment_tree() {}
	segment_tree(int N) : N(N) { t.resize(4 * (N + 1), T{0}); }
	segment_tree(vector<int> &arr) {        // ARRAY TYPE
		N = int(arr.size());
		t.resize(4 * (N + 1), T{0});
		build(1, 1, N, arr);
	}

	// Out of range
	T E() {
		return T{true, int(1e9), -1 * int(1e9)};
	}

	// Operation
	T combine(T a, T b) {
		T res;
		res.SORT = a.SORT and b.SORT and a.maxx <= b.minn;
		res.minn = min(a.minn, b.minn);
		res.maxx = max(a.maxx, b.maxx);
		return res;
	}

	void build(int n, int b, int e, vector<int>&a) {    // ARRAY TYPE
		if (b == e) {
			t[n] = {true, a[b - 1], a[b - 1]};                      // leaf nodes
			return;
		}
		int mid = (b + e) >> 1, l = n << 1, r = l | 1;
		build(l, b, mid, a);
		build(r, mid + 1, e, a);
		t[n] = combine(t[l], t[r]);
	}

	// t[n].value = x  -> To replace
	// t[n].value += x -> To add
	void update(int n, int b, int e, int i, TT x) {     // UPDATE TYPE
		if (b > i || e < i) return;
		if (b == e && b == i) {
			t[n] = {true, x, x};                             // update
			return;
		}
		int mid = (b + e) >> 1, l = n << 1, r = l | 1;
		update(l, b, mid, i, x);
		update(r, mid + 1, e, i, x);
		t[n] = combine(t[l], t[r]);
	}

	T query(int n, int b, int e, int i, int j) {
		if (b > j || e < i) return E();                 // appropiate value
		if (b >= i && e <= j) return t[n];
		int mid = (b + e) >> 1, l = n << 1, r = l | 1;
		T L = query(l, b, mid, i, j);
		T R = query(r, mid + 1, e, i, j);
		return combine(L, R);
	}

	// update
	void update(int l, TT x) { update(1, 1, N, l, x); }

	// query
	bool query(int l, int r) { T ans = query(1, 1, N, l, r); return ans.SORT; }
};