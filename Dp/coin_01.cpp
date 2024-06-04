const int sizee = int(1e7);
vector<int> taka(sizee + 1), paths(sizee + 1);
vector<int> coins;

// take min coin to make X taka
void calculation() {
	taka[0] = 0;
	for (int i = 1; i <= sizee; i++) {
		taka[i] = int(1e9);
		for (auto j : coins) {
			if (i - j >= 0 and taka[i - j] + 1 < taka[i]) {
				taka[i] = taka[i - j] + 1;
				paths[i] = j;
			}
		}
	}
}

void PRINT_COINT(int n) {
	while (n > 0) {
		cout << paths[n] << " ";
		n -= paths[n];
	}
	cout << endl;
}