// https://open.kattis.com/problems/10kindsofpeople

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

    int n, m;
    cin >> n >> m;

    vector<string> graph(n);
    for (auto &i : graph)
        cin >> i;

    int comp = 1;
    vector<vector<int>> component(n, vector<int>(m, false));
    vector<int> types{ -1};
    function<void(int, int, char, char)> floodfill = [&](int x, int y, char old, char replace) {
        if (x < 0 or x >= n)
            return;
        if (y < 0 or y >= m)
            return;
        if (graph[x][y] != old or graph[x][y] == '.')
            return;

        // each component size
        // int ans = 1;
        // ans += floodfill()
        graph[x][y] = replace;
        component[x][y] = comp;
        for (int i = 0; i < 4; i++)
            floodfill(x + dx[i], y + dy[i], old, replace);
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (graph[i][j] == '.') continue;

            types.push_back(graph[i][j] - '0');
            floodfill(i, j, graph[i][j], '.');
            comp++;
        }
    }

    int q;
    cin >> q;
    while (q--) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;

        r1--; c1--; r2--; c2--;

        if (component[r1][c1] != component[r2][c2]) {
            cout << "neither" << endl;
            continue;
        }

        cout << (types[component[r1][c1]] ? "decimal" : "binary") << endl;
    }
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