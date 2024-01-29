#include<bits/stdc++.h>
using namespace std;

struct node {
	using T = int;
	T summ, minn, maxx;
	int min_index = -1, max_index = -1;

	node() {}
	node(T v) { summ = v; minn = v; maxx = v; }
};

template<typename T = node>
struct segment_tree {
	using TT = typename node::T;

	int N;
	vector<T> t;

	T UNIT; // appropiate value
	T INIT = T(0);

	segment_tree() {}
	segment_tree(int N) : N(N) {
		t.resize(4 * (N + 1), INIT);
		UNIT.summ = 0;
		UNIT.maxx = numeric_limits<TT>::min();
		UNIT.minn = numeric_limits<TT>::max();
	}
	segment_tree(vector<int> &arr) {        // ARRAY TYPE
		N = int(arr.size());
		t.resize(4 * (N + 1), INIT);
		UNIT.summ = 0;
		UNIT.maxx = numeric_limits<TT>::min();
		UNIT.minn = numeric_limits<TT>::max();
		build(1, 1, N, arr);
	}

	T combine(T a, T b) {
		T res;
		res.summ = a.summ + b.summ;
		res.minn = min(a.minn, b.minn);
		res.maxx = max(a.maxx, b.maxx);
		res.min_index = (res.minn == a.minn ? a.min_index : b.min_index);
		res.max_index = (res.maxx == a.maxx ? a.max_index : b.max_index);
		return res;
	}

	void build(int n, int b, int e, vector<int>&a) {    // ARRAY TYPE
		if (b == e) {
			t[n].summ = a[b - 1];                      // leaf nodes
			t[n].minn = a[b - 1];
			t[n].maxx = a[b - 1];
			t[n].min_index = b;
			t[n].max_index = b;
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
			t[n].summ = x;                             // update
			t[n].minn = x;
			t[n].maxx = x;
			return;
		}
		int mid = (b + e) >> 1, l = n << 1, r = l | 1;
		update(l, b, mid, i, x);
		update(r, mid + 1, e, i, x);
		t[n] = combine(t[l], t[r]);
	}

	T query(int n, int b, int e, int i, int j) {
		if (b > j || e < i) return UNIT;                 // appropiate value
		if (b >= i && e <= j) return t[n];
		int mid = (b + e) >> 1, l = n << 1, r = l | 1;
		T L = query(l, b, mid, i, j);
		T R = query(r, mid + 1, e, i, j);
		return combine(L, R);
	}

	int kth(int n, int b, int e, int k) {
		if (b == e) return b;
		int mid = (b + e) >> 1, l = n << 1, r = l | 1;
		int value = t[l].summ;                           // left value
		if (k <= value) return kth(l, b, mid, k);
		else return kth(r, mid + 1, e, k - t[l].summ);   // goto right child
	};

	template <class F>
	int find_right(int n, int b, int e, int idx, F&& check) {
		if (b == e) return (check(t[n]) && b >= idx ? b : -1);
		int mid = (b + e) >> 1, l = n << 1, r = l | 1;
		int index = -1;
		if (check(t[l]) and mid >= idx) index = find_right(l, b, mid, idx, check);
		if (index == -1) index = find_right(r, mid + 1, e, idx, check);
		return index;
	}

	template <class F>
	int find_left(int n, int b, int e, int idx, F&& check) {
		if (b == e) return (check(t[n]) && b <= idx ? b : -1);
		int mid = (b + e) >> 1, l = n << 1, r = l | 1;
		int index = -1;
		if (check(t[l])) index = find_left(l, b, mid, idx, check);
		if (index == -1) index = find_left(r, mid + 1, e, idx, check);
		return index;
	}

	// position j such_that compare(NODE VALUE x) is TRUE and j >= l
	// position j such that x <= arr[j] and j >= l (maxx segment tree)
	// position j such that x >= arr[j] and j >= l (minn segment tree)
	template <class F>
	int find_right(int l, F&& check) { return find_right(1, 1, N, l, check); }

	// position j such_that compare(NODE VALUE x) is TRUE and j <= l
	// position j such that x <= arr[j] and j <= l (maxx segment tree)
	// position j such that x >= arr[j] and j <= l (minn segment tree)
	template <class F>
	int find_left(int l, F&& check) { return find_left(1, 1, N, l, check); }

	// position of kth element
	int kth(int k) { return t[1].summ < k ? -1 : kth(1, 1, N, k); }

	// update
	void update(int l, TT x) { update(1, 1, N, l, x); }

	// query
	TT query_sum(int l, int r) {
		T ans = query(1, 1, N, l, r);
		return ans.summ;
	}

	TT query_min(int l, int r) {
		T ans = query(1, 1, N, l, r);
		return ans.minn;
	}

	TT query_max(int l, int r) {
		T ans = query(1, 1, N, l, r);
		return ans.maxx;
	}

	TT query_min_index(int l, int r) {
		T ans = query(1, 1, N, l, r);
		return ans.min_index;
	}

	TT query_max_index(int l, int r) {
		T ans = query(1, 1, N, l, r);
		return ans.max_index;
	}
};

int32_t main() {

	ios::sync_with_stdio(false) ; cin.tie(0) ;

	int n;
	cin >> n;

	vector<int> arr(n);
	for (auto &i : arr)
		cin >> i;

	segment_tree<node> seg(n);       // empty segment tree of n size
	segment_tree<node> seg_arr(arr); // segment tree using arr

	cout << seg.query_sum(1, n) << endl;      // range_sum
	cout << seg_arr.query_min(1, n) << endl;  // range_min
	cout << seg.query_max(1, n) << endl;      // range_max
	cout << seg_arr.query_min_index(1, n) << endl; // range_min_index
	cout << seg_arr.query_max_index(1, n) << endl; // range_max_index


	// find position of kth one
	cout << seg_arr.kth(3) << endl;

	cout << seg_arr.find_right(2, [&](node A) { return A.maxx <= 10; } ) << endl;
	cout << seg_arr.find_left(2, [&](node A) { return A.minn >= 10; } ) << endl;

	return 0;
}
