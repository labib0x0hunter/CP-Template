vector<vector<pair<int, int>>> graph;

void init(int n) {
	graph.clear();

	graph.resize(n + 1);
}

void add_edge(int u, int v, int w) {
	graph[u].push_back({v, w});
	graph[v].push_back({u, w});
}

void graph_input(int n) {
	for (int i = 0; i < n; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		add_edge(u, v, w);
	}
}