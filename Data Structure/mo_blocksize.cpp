#include<bits/stdc++.h>
using namespace std;

struct Query { int idx, l, r; };
struct ANSWER { int value; };   // Change as ouput requires

int32_t main() {

	ios::sync_with_stdio(false) ; cin.tie(0) ;

	int t_c = 1, tt_c = 1; cin >> t_c;
	while (t_c--) {

		int n, q;
		cin >> n >> q;

		vector<int> arr(n);
		for (auto &i : arr)
			cin >> i;

		vector<Query> queries(q);
		for (int i = 0; i < q; i++) {
			int l, r;
			cin >> l >> r;
			queries[i].l = l - 1;
			queries[i].r = r - 1;
			queries[i].idx = i;
		}

		int block_size = 400;
		auto mo_cmp = [&](const Query & a, const Query & b) {
			int block_a = a.l / block_size;  // l1
			int block_b = b.l / block_size;  // l2
			// if same block then sort by r
			if (block_a == block_b) return a.r < b.r;
			// sort by l
			return a.l < b.l;
		};

		sort(queries.begin(), queries.end(), mo_cmp);

		int L = 0, R = -1;
		vector<ANSWER> ans(q);
		ANSWER result;
		result.value = 0;

		// ADD an element
		auto ADD = [&](int idx) {

		};

		// REMOVE an element
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
			ans[q.idx].value = result.value;
		}

		for (auto i : ans)
			cout << i.value << endl;

	}
	return 0;
}