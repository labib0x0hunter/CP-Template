int cmp, N, M;
vector<vector<int>> GRID;
vector<vector<int>> graph;

// first 4 are D, U, L, R
// last 4 are diagonal
vector<int> dx{1, -1, 0, 0, -1, -1, 1, 1};
vector<int> dy{0, 0, -1, 1, -1, 1, -1, 1};

bool valid(int i, int j) {
	if (i >= 0 and j >= 0 and i < N and j < M) {
		return true;
	}
	return false;
};

void init(int n, int m) {
	N = n, M = m, cmp = 1;
	GRID.resize(N, vector<int>(M, 0));
	graph.resize(N * M + 1);

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			GRID[i][j] = cmp++;
}

void convert(vector<string>& grid) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			for (int k = 0; k < 4; k++) { // Direction
				int x = i + dx[k];
				int y = j + dy[k];
				if (!valid(x, y)) continue;
				if (grid[i][j] != grid[x][y]) continue;
				int u = GRID[i][j];
				int v = GRID[x][y];
				if (u == v) continue;
				graph[u].emplace_back(v);   // Add edge
				// graph[v].emplace_back(u);
			}
		}
	}
}