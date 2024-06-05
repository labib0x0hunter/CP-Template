vector<int> spf_factor;
const int sizee = int(1e6);
void spf_sieve() {
	spf_factor.resize(sizee + 10);
	spf_factor[0] = spf_factor[1] = 1;
	for (int i = 2; i <= sizee; i += 2)
		spf_factor[i] = 2;
	for (int i = 3; i * i <= sizee; i += 2) {
		if (!spf_factor[i]) {
			spf_factor[i] = i;
			for (int j = i * i; j <= sizee; j += i)
				if (!spf_factor[j])
					spf_factor[j] = i;
		}
	}
	for (int i = 3; i <= sizee; i += 2)
		if (!spf_factor[i])
			spf_factor[i] = i;
}

vector<int> factorize(int n) {
	assert(!spf_factor.empty());
	assert(n <= sizee);
	vector<int> factor;
	while (n != spf_factor[n]) {
		factor.push_back(spf_factor[n]);
		n /= spf_factor[n];
	}
	if (n != 1)
		factor.push_back(n);
	return move(factor);
}