// CHange dist inf
template <typename T>
tuple<vector<T>, vector<int>, vector<int>> dijkstra(vector<int>& roots) {
	int N = graph.size();
	vector<T> dist(N + 1, infll); // inf / infll
	vector<int> par(N + 1, -1);
	vector<int> root(N + 1, -1);
	using P = pair<T, int>;

	priority_queue<P, vector<P>, greater<P>> que;

	for (auto v : roots) {
		dist[v] = 0;
		root[v] = v;
		que.emplace(0, v);
	}

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
			root[u] = root[s];
			que.push({dist[u], u});
		}
	}
	return {dist, par, root};
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
 * DIST, PAR, ROOT
 *
 *  auto djk = dijkstra<intll>(g, roots);

    auto dist = get<0>(djk);
    auto par = get<1>(djk);
    auto root = get<2>(djk);

    ORRR

    auto &&[dist, par, root] = dijkstra<intll>(g, roots);

 * */
