// first 4 are D, U, L, R
// last 4 are diagonal
vector<int> dx{1, -1, 0, 0, -1, -1, 1, 1};
vector<int> dy{0, 0, -1, 1, -1, 1, -1, 1};

function<void(int, int, char, char)> floodfill = [&](int x, int y, char old, char replace) {
	if (x < 0 or x >= n)
		return;
	if (y < 0 or y >= m)
		return;
	if (graph[x][y] != old)
		return;

	// each component size
	// int ans = 1;
	// ans += floodfill()
	graph[x][y] = replace;
	for (int i = 0; i < 8; i++)
		floodfill(x + dx[i], y + dy[i], old, replace);
};