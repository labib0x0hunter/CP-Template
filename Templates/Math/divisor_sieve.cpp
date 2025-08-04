const int sizee = int(2e5);
vector<vector<int>> divisors, prime_divisors;
void divisor_sieve() {
	divisors.resize(sizee + 10);
	prime_divisors.resize(sizee + 10);
	for (int i = 1; i <= sizee; i++) {
		for (int j = i; j <= sizee; j += i)
			divisors[j].push_back(i);
		if (i > 1 and prime_divisors[i].empty()) {
			for (int j = i; j <= sizee; j += i)
				prime_divisors[j].push_back(i);
		}
	}
}