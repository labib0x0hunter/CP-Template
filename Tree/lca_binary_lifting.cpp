#include<bits/stdc++.h>
using namespace std;

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
	assert(k >= 0 and k < depth[u]);
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

int32_t main() {

	ios::sync_with_stdio(false) ; cin.tie(0) ;

	int n;
	cin >> n;

	init(n);

	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;

		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	dfs(1, 0);

	// depth of 5 is 3
	cout << kth_ancestor(5, 0) << endl;
	cout << kth_ancestor(5, 1) << endl;
	cout << kth_ancestor(5, 2) << endl;
	// cout << kth_ancestor(5, 3) << endl; // assert Failed

	// d1, d2 is diameter node
	cout << kth_node_from_u_to_v(d1, d2, 3) << endl;

	return 0;
}