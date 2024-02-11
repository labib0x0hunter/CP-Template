#include<bits/stdc++.h>
using namespace std;

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
};

// Range Update Range Query
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

	// add x to every element from arr[i] to arr[j]
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

int32_t main() {

	ios::sync_with_stdio(false) ; cin.tie(0) ;

	int n;
	cin >> n;

	vector<int> arr(n);
	for (auto &i : arr)
		cin >> i;

	// point update range query
	// 1-index based
	binary_index_tree<long long> bit(arr);
	// binary_index_tree<long long> bit(n);

	// point update
	bit.update(4, 100); 		  // add 100 to arr[4]
	// range update (add to range)
	bit.range_update(2, 4, 100);  // add 100 from arr[2] to arr[4]
	// point query
	cout << bit.query(4) << endl; // get arr[1] + arr[2] + arr[3] + arr[4]
	// range query
	// query(r) - query(l - 1)
	cout << bit.query(4) - bit.query(1) << endl; // get arr[2] + arr[3] + arr[4]


	// range update range query
	RURQ<long long> bit2(arr);
	// RURQ<long long> bit2(n);
	
	// range update
	bit2.range_update(1, 4, 100);    // add 100 to arr[1], arr[2], arr[3], arr[4]
	// point query
	cout << bit2.query(4) << endl;   // get arr[1] + arr[2] + arr[3] + arr[4]
	// range query
	cout << bit2.query(4) - bit2.query(2) << endl; // get arr[3] + arr[4]

	return 0;
}
