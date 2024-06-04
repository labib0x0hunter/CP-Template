// use sum segment tree
vector<vector<pair<int, int>>> queries(n + 1);
queries[l].push_back({r, i});

map<int, int> mp;
vector<int> ans(n + 1);
for (int i = n; i > 0; i--) {
	int val = arr[i - 1];
	if (mp.find(val) != mp.end())
		seg.update(mp[val], 0); // Replace in segment tree node (**)
	seg.update(i, 1);
	mp[val] = i;
	for (auto [l, id] : queries[i])
		ans[id] = seg.query_sum(1, l);
}