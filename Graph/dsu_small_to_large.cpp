struct dsu {
	vector<int> parent, nodes, sizee;
	vector<vector<int>> graph;
	vector<multiset<int>> component_elements;
	int N;
	int component;

	dsu(int n) : N(n) {
		sizee.resize(N + 1, 1);
		parent.resize(N + 1, -1);
		nodes.resize(N + 1);
		graph.resize(N + 1);
		iota(nodes.begin(), nodes.end(), 0);
		component = n;

		component_elements.resize(N + 1);
		for (int i = 1; i <= N; i++) {
			component_elements[i].insert(i);
		}
	}

	int find_parent(int x) {
		return nodes[x] == x ? x : nodes[x] = find_parent(nodes[x]);
	}

	bool same_set(int x, int y) {
		return find_parent(x) == find_parent(y);
	}

	int size(int x) {
		return sizee[find_parent(x)];
	}

	int count() {
		return component;
	}

	// bool merge(int x, int y) {  // union by size
	// 	x = find_parent(x);
	// 	y = find_parent(y);
	// 	if (x == y) return false;
	// 	sizee[x] += sizee[y];
	// 	nodes[y] = x;
	// 	component--;
	// 	return true;
	// }

	// void unite(int x, int y) {
	// 	if (sizee[find_parent(x)] > sizee[find_parent(y)])
	// 		swap(x, y);
	// 	dfs(x, y);
	// 	merge(x, y);
	// 	graph[x].push_back(y);
	// 	graph[y].push_back(x);
	// }

	void dfs(int s, int p) {
		parent[s] = p;
		for (int u : graph[s]) {
			if (u == p) continue;
			dfs(u, s);
		}
	}


	bool merge(int x, int y) {  // Union by size
		x = find_parent(x);
		y = find_parent(y);
		if (x == y) return false;
		if (sizee[x] < sizee[y]) {
			swap(x, y);
		}

		// Apply small to large
		for (int u : component_elements[y])
			component_elements[x].insert(u);

		nodes[y] = x;
		sizee[x] += sizee[y];
		component--;
		return true;
	}

	int kth(int x, int k) {
		x = find_parent(x);
		if (k < 0 || k >= int(component_elements[x].size())) return -1;
		auto it = component_elements[x].rbegin(); // largest or smallest
		advance(it, k);
		return *it;
	}
};
