// first 4 are D, U, L, R
// last 4 are diagonal
vector<int> dx{1, -1, 0, 0, -1, -1, 1, 1};
vector<int> dy{0, 0, -1, 1, -1, 1, -1, 1};
queue<pair<int, int>> que;
vector<vector<bool>> visited(n, vector<bool>(m, false));

auto valid = [&](int i, int j) -> bool {
	if (i >= 0 and j >= 0 and i < n and j < m) {
		if (visited[i][j] == false) return true;
	}
	return false;
};

auto bfs = [&](int i, int j) -> void {
	que.push({i, j});
	visited[i][j] = true;
	while (!que.empty()) {
		auto &[x, y] = que.front(); que.pop();
		for (int i = 0; i < 4; i++) {
			int xx = x + dx[i];
			int yy = y + dy[i];

			if (valid(xx, yy)) {
				que.push({xx, yy});
				visited[xx][yy] = true;
			}
		}
	}
};