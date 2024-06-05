const int sizee = int(1e6) + 1;
vector<bool> bs(sizee + 10);
vector<int> primes{2};

void sieve() {
	bs[0] = bs[1] = 1;
	for (int i = 3; i * i <= sizee; i += 2) {
		if (bs[i]) continue;
		for (int j = i * i; j <= sizee; j += i)
			bs[j] = 1;
	}

	for (int i = 3; i <= sizee; i += 2)
		if (!bs[i]) primes.push_back(i);
}

// ai <= n or ai <= sizee
bool is_prime(int x) {
	assert(x <= sizee);
	if (x == 2) return 1;
	if (x % 2 == 0) return 0;
	return (!bs[x]);
}