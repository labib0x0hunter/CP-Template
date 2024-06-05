// CHange dist inf
template <typename T>
pair<vector<T>, vector<int>> dijkstra(int root) {
	int N = graph.size();
	vector<T> dist(N + 1, infll); // inf / infll
	vector<int> par(N + 1, -1);
	using P = pair<T, int>;

	priority_queue<P, vector<P>, greater<P>> que;

	dist[root] = 0;
	que.emplace(0, root);

	while (!que.empty()) {
		auto [d, s] = que.top();
		que.pop();
		if (d > dist[s])
			continue;
		for (auto &[u, w] : graph[s]) {
			if (dist[s] + w >= dist[u])
				continue;
			dist[u] = dist[s] + w;
			par[u] = s;
			que.push({dist[u], u});
		}
	}
	return {dist, par};
}

// distance -> parent -> source -> destination
template<typename T = int>
vector<int> get_path(vector<T>& dist, vector<int> par, int source, int final) {

	if (dist[final] == infll) // inf / infll
		return vector<int> { -1};
	vector<int> path;
	for (int i = final; i != source; i = par[i])
		path.push_back(i);
	path.push_back(1);
	ranges::reverse(path);

	return path;
}

// RETURNS
/**
 *  auto [dist, par] = dijkstra<intll>(graph, source);
 *
 *
 * */