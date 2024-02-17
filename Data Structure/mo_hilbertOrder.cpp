#include<bits/stdc++.h>
using namespace std;

inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) { return 0; }
	int hpow = 1 << (pow - 1);
	int seg = (x < hpow) ? ( (y < hpow) ? 0 : 3) :
	          ( (y < hpow) ? 1 : 2);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2 * pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = hilbertOrder(nx, ny, pow - 1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

struct Query {
	int l, r, index;
	int64_t idx;
	inline void get_order() {
		idx = hilbertOrder(l, r, 21, 0);
	}
};

struct ANSWER { int idx, L, R; };   // Change as output requires

int32_t main() {

	ios::sync_with_stdio(false) ; cin.tie(0) ;

	int t_c = 1, tt_c = 1; cin >> t_c;
	while (t_c--) {

		int n, q;
		cin >> n;

		vector<int> arr(n);
		for (auto &i : arr)
			cin >> i;

		cin >> q;
		vector<Query> queries(q);
		for (int i = 0; i < q; i++) {
			int l, r;
			cin >> l >> r;
			queries[i].l = l - 1;
			queries[i].r = r - 1;
			queries[i].index = i;
			queries[i].get_order();
		}

		sort(queries.begin(), queries.end(), [&](const Query & a, const Query & b) {
			return a.idx < b.idx;
		});

		int L = 0, R = -1;
		vector<ANSWER> ans(q);
		ANSWER result;
		result.L = -1;
		result.R = -1;

		// Add an element
		auto ADD = [&](int idx) {

		};
		// Remove an element
		auto REMOVE = [&](int idx) {

		};

		for (auto q : queries) {
			while (L > q.l) {
				--L;
				ADD(L);
			}
			while (R < q.r) {
				++R;
				ADD(R);
			}
			while (L < q.l) {
				REMOVE(L);
				++L;
			}
			while (R > q.r) {
				REMOVE(R);
				--R;
			}
			ans[q.index].L = result.L;
			ans[q.index].R = result.R;
		}

		for (auto i : ans)
			cout << i.L << " " << i.R << endl;

	}
	return 0;
}
