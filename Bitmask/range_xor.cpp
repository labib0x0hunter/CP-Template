// gives 1 ^ 2 ^ ... ^ n
template<typename T = int>
T findXOR(T n) {
	int mod = n % 4;
	if (mod == 0) return n;
	if (mod == 1) return 1;
	if (mod == 2) return n + 1;
	if (mod == 3) return 0;
}