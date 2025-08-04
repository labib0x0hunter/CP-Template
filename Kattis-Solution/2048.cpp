// https://open.kattis.com/problems/2048

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

// cc = counter_clockwise
template <typename T = vector<int>>
vector<T> rotate90(int n, int m, vector<T>& Arr, bool cc = true) {
    vector<T> Brr(m, T(n, Arr[0][0]));
    if (cc) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                Brr[m - 1 - j][i] = Arr[i][j];
    }
    else {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                Brr[j][n - 1 - i] = Arr[i][j];
    }
    return Brr;
}

void solution() {

    int n = 4;
    vector<vector<int>> grid(n, vector<int>(n));

    for (auto &i : grid)
        for (auto &j : i)
            cin >> j;

    int k;
    cin >> k;

    for (int i = 0; i < k; i++) {
        auto grid_temp = rotate90(n, n, grid);
        grid = grid_temp;
    }

    auto set_order = [](vector<int>& arr) {
        vector<int> brr;
        int I = 0;
        for (int i = 0; i < 4; i++) {
            if (arr[i] == 0) continue;
            brr.push_back(arr[i]);
            I = i;
            break;
        }

        bool merged = false;
        for (int i = I + 1; i < 4; i++) {
            if (arr[i] == 0) continue;
            if (arr[i] == brr.back() and merged == false) {
                brr.back() += arr[i];
                merged = true;
            }
            else {
                brr.push_back(arr[i]);
                merged = false;
            }
        }
        arr = brr;
        while (arr.size() < 4)
            arr.push_back(0);
    };

    for (auto &i : grid) {
        // PRINT(i);
        set_order(i);
    }

    for (int i = 0; i < (4 - k); i++) {
        auto grid_temp = rotate90(n, n, grid);
        grid = grid_temp;
    }

    for (auto i : grid) {
        PRINT(i);
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