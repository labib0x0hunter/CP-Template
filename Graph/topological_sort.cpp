vector<int> topological_sort(vector<int>& indegree) {
	int N = graph.size() - 1;
	vector<int> topo;
	priority_queue<int, vector<int>, greater<int>> zero;

	for (int i = 1; i <= N; i++) {
		if (indegree[i] == 0)
			zero.push(i);
	}

	while (!zero.empty()) {
		int source = zero.top();
		zero.pop();
		topo.emplace_back(source);

		for (auto [u, _] : graph[source]) {
			indegree[u]--;
			if (indegree[u] == 0)
				zero.push(u);
		}
	}
	return topo;
}