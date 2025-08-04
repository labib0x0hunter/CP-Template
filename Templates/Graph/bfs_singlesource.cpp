
// {dist, parent}
pair<vector<int>, vector<int>> bfs(int source) {

	int N = graph.size() - 1;
	vector<int> parent(N + 1, -1), dist(N + 1, -1);
	queue<int> que;


	que.push(source);
	dist[source] = 0;

	while (!que.empty()) {
		auto s = que.front();
		que.pop();
		for (auto &[u, w1] : graph[s]) {
			if (dist[u] == -1) {
				dist[u] = dist[s] + w1;
				parent[u] = s;
				que.push(u);
			}
		}
	}
	return make_pair(dist, parent);
}