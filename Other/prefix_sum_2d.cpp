template<typename T = int>
struct prefix_sum_2D {

	int N, M;
	vector<vector<T>> summ2D;
	prefix_sum_2D(vector<vector<int>> &arr) {
		N = int(arr.size()); M = int(arr[0].size());
		summ2D.resize(N + 1, vector<T> (M + 1, 0));

		summ2D[1][1] = arr[0][0];
		for (int i = 1; i < N; i++) summ2D[1][i + 1] = summ2D[1][i] + arr[0][i];
		for (int i = 1; i < M; i++) summ2D[i + 1][1] = summ2D[i][1] + arr[i][0];
		for (int i = 1; i < N; i++) {
			for (int j = 1; j < M; j++) {
				summ2D[i + 1][j + 1] = summ2D[i + 1][j] + summ2D[i][j + 1] - summ2D[i][j] + arr[i][j];
			}
		}
	}

	T query(int l1, int r1, int l2, int r2) {
		return summ2D[l2][r2] - summ2D[l1 - 1][r2] - summ2D[l2][r1 - 1] + summ2D[l1 - 1][r1 - 1];
	}
};

/**
 * prefix_sum_2D s(arr);
 * s.get_sum(l1, r1, l2, r2)
 * */