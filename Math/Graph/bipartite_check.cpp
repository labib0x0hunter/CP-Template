bool Bp = true;
int Zero = 0, One = 0;
vector<bool> visited(n + 1, false);
vector<int> col(n + 1, false);

function<void(int)> dfs = [&](int s) {
	visited[s] = true;
	for (auto u : graph[s]) {
		if (!visited[u]) {
			col[u] = 1 - col[s];
			dfs(u);
		}
		else if (col[u] == col[s]) {
			// Not Bipartite
			Bp = false;
		}
	}
	// Zero += col[s] == 0;
	// One += col[s] == 1;
};

for (int i = 1; i <= n; i++) {
	if (visited[i]) continue;
	Bp = true; Zero = One = 0;
	dfs(i);
}