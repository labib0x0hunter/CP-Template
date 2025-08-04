// https://open.kattis.com/problems/8queens

#include<bits/stdc++.h>
using namespace std;

#define intll long long
#define endl '\n'
#define TEST_CASE false

template<typename T>
void PRINT(vector<T>& arr) {
	for (int i = 0; i < int(arr.size()); i++)
		cout << arr[i] << " \n"[i == int(arr.size()) - 1];
}

vector<int> dx{1, -1, 0, 0, -1, -1, 1, 1};
vector<int> dy{0, 0, -1, 1, -1, 1, -1, 1};

void solution() {

	int n = 8;
	vector<string> board(n);
	for (auto &c : board)
		cin >> c;

	auto valid = [&](int i, int j) -> bool {
		if (i >= 0 and j >= 0 and i < n and j < n) {
			return true;
		}
		return false;
	};

	int queen = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i][j] == '.') continue;
			queen++;
			for (int dir = 0; dir < 8; dir++) {
				int x = i, y = j;
				while (1) {
					int X = x + dx[dir];
					int Y = y + dy[dir];
					if (!valid(X, Y)) break;
					if (board[X][Y] == '*') {
						cout << "invalid" << endl;
						return;
					}
					x = X, y = Y;
				}
			}
		}
	}

	cout << (queen == 8 ? "valid" : "invalid") << endl;
}

int32_t main() {

	ios::sync_with_stdio(false) ; cin.tie(0) ;

	int t_c = 1, tt_c = 1;
	if (TEST_CASE) cin >> t_c;

	while (t_c--) {
		// cout << "Case " << tt_c++ << ": ";
		solution();
		// if (t_c) cout << '\n';
	}

	return 0;
}