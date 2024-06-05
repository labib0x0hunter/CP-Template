template<typename T = int>
T add_mod(T a, T b, T mod) {
	a = a % mod;
	b = b % mod;
	return (((a + b) % mod) + mod) % mod;
}

template<typename T = int>
T mult_mod(T a, T b, T mod) {
	a = a % mod;
	b = b % mod;
	return (((1ll * a * b) % mod) + mod) % mod;
}

template<typename T = int>
T subs_mod(T a, T b, T mod) {
	a = a % mod;
	b = b % mod;
	return (((a - b) % mod) + mod) % mod;
}

template<typename T = int>
T extgcd(T a, T b, T &x, T &y) {
	T xx = y = 0;
	T yy = x = 1;
	while (b) {
		T q = a / b;
		T t = b; b = a % b; a = t;
		t = xx; xx = x - 1ll * q * xx; x = t;
		t = yy; yy = y - 1ll * q * yy; y = t;
	}
	return a;
}

template<typename T = int>
T div_mod(T a, T b, T mod) {
	T x, y;
	T d = extgcd<T>(b, mod, x, y);
	if (d != 1) return -1;
	return (mult_mod<T>(a, x, mod) + mod) % mod;
}

template<typename T = int>
T expo(T x, T y, T mod) {
	T res = 1;
	x = x % mod;
	if (x == 0) return 0;
	while (y > 0) {
		if (y & 1) res = (1ll * res * x) % mod;
		y = y >> 1;
		x = (1ll * x * x) % mod;
	}
	return (res + mod) % mod;
}