#include<bits/stdc++.h>
using namespace std;

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

int32_t main() {

	ios::sync_with_stdio(false) ; cin.tie(0) ;

	int a, b;
	cin >> a >> b;

	const int mod = int(1e9) + 7;

	auto A1 = add_mod(a, b, mod);  // (a + b) % mod
	auto A2 = subs_mod(a, b, mod); // (a - b) % mod
	auto A3 = mult_mod(a, b, mod); // (a * b) % mod
	auto A4 = div_mod(a, b, mod); // (a / b) % mod

	auto A5 = expo(a, b, mod); // (a ^ b) % mod

	long long x, y;                               // if gcdd != 1, then a has no inverse
	auto gcdd = extgcd<long long>(a, mod, x, y);  // x is inverse of a -> (1 / a) % mod
	x = add_mod<long long>(x, mod, mod);

	return 0;
}
