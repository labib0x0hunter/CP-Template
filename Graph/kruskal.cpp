struct UVW { int u, v; intll w; };

struct dsu {
	vector<int> nodes;
	int component;
	int N;

	dsu() {}
	dsu(int n) : N(n) {
		nodes = vector<int>(N + 1, -1);
		component = N;
	}

	void resize(int n) {
		N = n;
		nodes = vector<int>(N + 1, -1);
		component = N;
	}

	// find parent or get representive component (uses path compression)
	int find_parent(int x) {
		return nodes[x] < 0 ? x : nodes[x] = find_parent(nodes[x]);
	}

	bool same_set(int a, int b) {
		return find_parent(a) == find_parent(b);
	}

	bool unite(int x, int y) {  // union by size
		x = find_parent(x);
		y = find_parent(y);

		if (x == y)
			return false;
		if (nodes[x] > nodes[y])
			swap(x, y);

		nodes[x] += nodes[y];
		nodes[y] = x;
		component--;
		return true;
	}
};

template<typename T = int>
struct kruskal {
	int N, edge_taken;
	T mst_cost;
	vector<array<int, 2>> tree;

	vector<UVW> edges;
	dsu d;

	kruskal(int n) : N(n) {
		d.resize(N);
		mst_cost = 0;
		edge_taken = 0;
	}

	void build_mst(int m) {
		edges.resize(m);
		for (auto &[u, v, w] : edges)
			cin >> u >> v >> w;
		sort(edges.begin(), edges.end(), [&](UVW & a, UVW & b) { return a.w < b.w; });
		for (auto &[u, v, w] : edges) {
			if (d.same_set(u, v))
				continue;
			d.unite(u, v);
			tree.push_back({u, v});

			mst_cost += w;
			edge_taken++;
			if (edge_taken == N - 1)
				break;
		}
	}
};

/**
 * n = nodes, m = edges;
 *
 * kruskal<intll> mst(n);
 * mst.build_mst(m);
 *
 * spanning tree minimum cost = mst.mst_cost
 *
 * */