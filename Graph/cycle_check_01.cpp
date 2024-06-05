// directed graph
vector<int> col(n + 1, 0), parent(n + 1, -1);
bool cycle = false;

function<void(int)> dfs = [&](int source) {
	col[source] = 1;
	for (auto u : graph[source]) {
		if (col[u] == 0) {
			parent[u] = source;
			dfs(u);
		}
		else if (col[u] == 1) {
			cycle = true;
		}
	}
	col[source] = 2;
};