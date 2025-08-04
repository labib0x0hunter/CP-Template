const int sizee = int(1e6) + 1;
vector<int> NOD(sizee + 10);

void NOD_sieve() {
	for (int i = 1; i <= sizee; i++)
		for (int j = i; j <= sizee; j += i)
			NOD[j]++;
}