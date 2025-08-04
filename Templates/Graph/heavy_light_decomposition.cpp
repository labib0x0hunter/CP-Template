vector<vector<int>> graph;
vector<int> depth, subtree_size;
vector<int> heavy_root, parent;
vector<int> first_seen, last_seen;
vector<int> euler, tour_list;
vector<vector<int>> rmq_table;
vector<int> tour_start;
int tour;
bool edge_mode = true;
segment_tree_lazy<node> seg;  // segment tree

void init(int N) {
	graph.clear();
	depth.clear();
	subtree_size.clear();
	euler.clear();
	tour_list.clear();
	first_seen.clear();
	heavy_root.clear();
	parent.clear();

	tour = 1;
	graph.resize(N + 1);
	depth.resize(N + 1, 0);
	subtree_size.resize(N + 1, 0);
	heavy_root.resize(N + 1, 0);
	parent.resize(N + 1, 0);

	euler.emplace_back(0);
	tour_list.resize(N + 1, 0);
	first_seen.resize(N + 1, 0);
	tour_start.resize(N + 1);
	seg = segment_tree_lazy<node>(N);  // segment tree
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
	graph[s].erase(remove(graph[s].begin(), graph[s].end(), par), graph[s].end());
	for (int u : graph[s]) {
		dfs_subtree(u, s);
		subtree_size[s] += subtree_size[u];
	}
	sort(graph[s].begin(), graph[s].end(), [&](int a, int b) {
		return subtree_size[a] > subtree_size[b];
	});
}

void dfs(int s, bool heavy) {
	heavy_root[s] = heavy ? heavy_root[parent[s]] : s;
	first_seen[s] = int(euler.size());
	euler.emplace_back(s);
	tour_start[s] = tour;
	tour++;
	bool is_heavy = true;
	for (auto u : graph[s]) {
		dfs(u, is_heavy);
		euler.emplace_back(s);
		is_heavy = false;
	}
}

void build_rmq() {
	int NN = 2 * (int(graph.size()) - 1) + 1;
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

// log(n)
int lca(int x, int y) {
	for (; heavy_root[x] != heavy_root[y]; y = parent[heavy_root[y]])
		if (depth[heavy_root[x]] > depth[heavy_root[y]]) swap(x, y);
	return depth[x] < depth[y] ? x : y;
}

template <class F>
void processPath(int x, int y, F&& op) {
	for (; heavy_root[x] != heavy_root[y]; y = parent[heavy_root[y]]) {
		if (depth[heavy_root[x]] > depth[heavy_root[y]]) swap(x, y);
		op(tour_start[heavy_root[y]], tour_start[y]);
	}
	if (depth[x] > depth[y]) swap(x, y);
	op(tour_start[x] + edge_mode, tour_start[y]);
}

void modifyPath(int x, int y, int v) {
	processPath(x, y, [&](int l, int r) {
		seg.update(l, r, v);
	});
}

long long queryPath(int x, int y) {
	long long res = 0; processPath(x, y, [&](int l, int r) {
		res += seg.query(l, r);
	});
	return res;
}

void modifySubtree(int x, int v) {
	seg.update(tour_start[x] + edge_mode, tour_start[x] + subtree_size[x] - 1, v);
}

// Need to check
long long querySubtree(int x) {
	return seg.query(tour_start[x], tour_start[x] + subtree_size[x] - 1);
}

// edge_mode = true / false