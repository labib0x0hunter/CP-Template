template<typename T = int>
vector<T> get_divisors(T n) {
	vector<int> div;
	for (int i = 1; 1ll * i * i <= n; i++) {
		if (n % i) continue;
		div.emplace_back(i);
		if (1ll * i * i == n) continue;
		div.emplace_back(n / i);
	}
	ranges::sort(div);
	return move(div);
}