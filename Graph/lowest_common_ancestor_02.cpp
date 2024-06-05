vector<vector<int>> graph;
vector<int> depth;
vector<vector<int>> parent;
int LOGG;

void init(int N) {
	graph.clear();
	depth.clear();
	parent.clear();

	LOGG = log2(N) + 1;
	graph.resize(N + 1);
	depth.resize(N + 1, 0);
	parent.resize(N + 1, vector<int>(LOGG + 1));
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

void dfs(int s, int par) {
	parent[s][0] = par;
	depth[s] = depth[par] + 1;

	for (int i = 1; i <= LOGG; i++)
		parent[s][i] = parent[parent[s][i - 1]][i - 1];

	for (auto v : graph[s])
		if (v != par) {
			dfs(v, s);
		}
}

// log(n)
int get_lca(int u, int v) {
	if (depth[u] < depth[v])
		swap(u, v);

	for (int k = LOGG; k >= 0; k--) {
		if (depth[parent[u][k]] >= depth[v])
			u = parent[u][k];
	}

	if (u == v)
		return u;

	for (int k = LOGG; k >= 0; k--) {
		if (parent[u][k] != parent[v][k]) {
			u = parent[u][k];
			v = parent[v][k];
		}
	}
	return parent[u][0];
};

// kth ancestor of node u
// k is 0-based index
int kth_ancestor(int u, int k) {
	if (k < 0 and k > depth[u]) return -1;
	for (int i = 0; i <= LOGG; i++)
		if (k & (1 << i))
			u = parent[u][i];
	return u;
}

// distance between u and v
int dist(int u, int v) {
	int l = get_lca(u, v);
	return depth[u] + depth[v] - (depth[l] << 1);
}

//kth node from u to v, 0th node is u
int kth_node_from_u_to_v(int u, int v, int k) {
	int l = get_lca(u, v);
	int d = depth[u] + depth[v] - (depth[l] << 1);
	assert(k <= d);
	if (depth[l] + k <= depth[u])
		return kth_ancestor(u, k);
	k -= depth[u] - depth[l];
	return kth_ancestor(v, depth[v] - depth[l] - k);
}