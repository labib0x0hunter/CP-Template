vector<vector<int>> graph;
vector<int> depth, subtree_size;
vector<int> heavy_root, parent;
vector<int> first_seen, last_seen;
vector<int> euler, tour_list;
vector<vector<int>> rmq_table;
vector<int> tour_start;
int tour;

void init(int N) {
	graph.clear();
	depth.clear();
	subtree_size.clear();
	euler.clear();
	tour_list.clear();
	first_seen.clear();
	last_seen.clear();
	heavy_root.clear();
	parent.clear();
	tour_start.clear();

	tour = 1;
	graph.resize(N + 1);
	depth.resize(N + 1, 0);
	subtree_size.resize(N + 1, 0);
	heavy_root.resize(N + 1, 0);
	parent.resize(N + 1, 0);

	euler.emplace_back(0);
	tour_list.resize(N + 1, 0);
	first_seen.resize(N + 1, 0);
	last_seen.resize(N + 1);
	tour_start.resize(N + 1);
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

void dfs_subtree(int s, int par) {
	subtree_size[s] = 1;
	parent[s] = par;
	depth[s] = depth[par] + 1;

	// ERASE edge to it's parent
	graph[s].erase(remove(graph[s].begin(), graph[s].end(), par), graph[s].end());

	for (int u : graph[s]) {
		dfs_subtree(u, s);
		subtree_size[s] += subtree_size[u];
	}
	// Heavy-light subtree reordering
	sort(graph[s].begin(), graph[s].end(), [&](int a, int b) {
		return subtree_size[a] > subtree_size[b];
	});
}

void dfs(int s, bool heavy) {
	heavy_root[s] = heavy ? heavy_root[parent[s]] : s;
	first_seen[s] = int(euler.size());
	euler.emplace_back(s);
	tour_list[tour] = s;
	tour_start[s] = tour;
	tour++;
	bool is_heavy = true;

	for (auto u : graph[s]) {
		dfs(u, is_heavy);
		euler.emplace_back(s);
		is_heavy = false;
	}
	last_seen[s] = int(euler.size());
}

void build_rmq() {
	rmq_table.clear();
	int NN = int(euler.size()) - 1;
	rmq_table.resize(NN + 1, vector<int> (log2(NN) + 1, -1));

	for (int i = 1; i <= NN; ++i)
		rmq_table[i][0] = i;

	for (int k = 1; (1 << k) <= NN; ++k) {
		for (int i = 1; i + (1 << k) - 1 < NN; ++i) {
			int l = rmq_table[i][k - 1];
			int r = rmq_table[i + (1 << (k - 1))][k - 1];
			int l_p = euler[l];
			int r_p = euler[r];
			rmq_table[i][k] = (depth[l_p] < depth[r_p] ? l : r);
		}
	}
}

int get_lca(int l, int r) {
	assert(rmq_table.empty() == false);

	l = first_seen[l];
	r = first_seen[r];
	if (l > r) swap(r, l);

	int k = log2(r - l + 1);
	l = rmq_table[l][k];
	r = rmq_table[r - (1 << k) + 1][k];

	int lcaa = (depth[euler[l]] < depth[euler[r]] ? l : r);
	return euler[lcaa];
}

// a = ancestor of b
bool is_ancestor(int a, int b) {
	return first_seen[a] <= first_seen[b] && first_seen[b] < last_seen[a];
}

// distance from node a to node b
int dist(int a, int b) {
	return depth[a] + depth[b] - 2 * depth[get_lca(a, b)];
}

// x lies between a to b
bool on_path(int x, int a, int b) {
	return (is_ancestor(x, a) || is_ancestor(x, b)) && is_ancestor(get_lca(a, b), x);
}

pair<int, int> get_diameter(int N) {
	array<int, 2> diam{1, 1}; // change root
	for (int c = 1; c <= N; c++) {
		auto [a, b] = diam;
		int ab = dist(a, b);
		int ac = dist(a, c);
		int bc = dist(b, c);
		int maxx = max({ab, ac, bc});

		if (maxx == ab) continue;
		if (maxx == ac) diam = {a, c};
		if (maxx == bc) diam = {b, c};
	}
	return make_pair(diam[0], diam[1]);
}

vector<int> get_paths(int u, int v) {
	if (depth[u] > depth[v]) swap(u, v);
	vector<int> path;
	while (u != v) {
		path.push_back(v);
		v = parent[v];
	}
	path.push_back(u);
	return move(path);
}

// k is 0 index-based
// output 0 means ROOT of root
int kth_ancestor(int u, int k) {
	if (k > depth[u]) return -1;
	while (u >= 1) {
		int root = heavy_root[u];
		if (depth[root] <= depth[u] - k)
			return tour_list[tour_start[u] - k]; // sometimes k - 1 gives Ac, Sometimes WA
		k -= depth[u] - depth[root] + 1;
		u = parent[root];
	}
	return u;
}

int get_kth_node_on_path(int a, int b, int k) {
	int anc = get_lca(a, b);
	int first_half = depth[a] - depth[anc];
	int second_half = depth[b] - depth[anc];
	if (k < 0 || k > first_half + second_half)
		return -1;
	if (k < first_half)
		return kth_ancestor(a, k);
	else
		return kth_ancestor(b, first_half + second_half - k);
}