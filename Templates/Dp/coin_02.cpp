const int sizee = int(1e6 + 1);
vector<mint> taka(sizee + 1);
vector<int> coins;

// how many ways to make X taka
void calculation() {
	taka[0] = mint(1);
	for (int i = 0; i <= sizee; i++) {
		for (auto j : coins) {
			if (i - j >= 0) {
				taka[i] += taka[i - j];
			}
		}
	}
}