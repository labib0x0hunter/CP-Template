int expo(intll x, int y, int p) {
	int res = 1;
	x = x % p;
	if (x == 0) return 0;

	while (y > 0) {
		if (y & 1) res = (1ll * res * x) % p;

		y = y >> 1;
		x = (1ll * x * x) % p;
	}
	return (res + p) % p;
}