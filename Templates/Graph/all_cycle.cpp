vector<vector<int>> cycles;
vector<int> color(n + 1), par(n + 1);

function<void(int, int)> dfs_cycle = [&](int u, int p) {
	if (color[u] == 2)
		return;

	if (color[u] == 1) {
		vector<int> v;
		int cur = p;
		v.push_back(cur);
		while (cur != u) {
			cur = par[cur];
			v.push_back(cur);
		}
		cycles.push_back(v);
		return;
	}
	par[u] = p;
	color[u] = 1;
	for (int v : graph[u]) { // Graph name
		if (v != par[u])
			dfs_cycle(v, u);
	}
	color[u] = 2;
};

dfs_cycle(1, 0);