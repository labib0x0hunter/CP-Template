vector<vector<int>> graph;

void init(int n) {
	graph.clear();

	graph.resize(n + 1);
}

void add_edge(int u, int v) {
	graph[u].push_back(v);
	graph[v].push_back(u);
}

void graph_input(int n) {
	for (int i = 0; i < n; i++) {
		int u, v;
		cin >> u >> v;
		add_edge(u, v);
	}
}

void graph_input_line(int n) {
	for (int i = 2; i <= n; i++) {
		int u;
		cin >> u;
		add_edge(u, i);
	}
}