#include<bits/stdc++.h>
using namespace std;

#define intll long long
#define endl '\n'
#define TEST_CASE true

template<typename T>
void PRINT(vector<T>& arr) {
	for (int i = 0; i < int(arr.size()); i++)
		cout << arr[i] << " \n"[i == int(arr.size()) - 1];
}

void solution() {

	int n;
	cin >> n;

	vector<int> arr(n);
	for (auto &i : arr)
		cin >> i;

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