// undirected graph
vector<int> col(n + 1, 0), parent(n + 1, -1);
bool cycle = false;

function<void(int)> dfs = [&](int source) {
	col[source] = 1;
	for (auto u : graph[source]) { // Graph name
		if (col[u] == 0) {
			parent[u] = source;
			dfs(u);
		}
		else if (col[u] == 1 and parent[source] != u) {
			cycle = true;
		}
	}
	col[source] = 2;
};