struct Mint {
	uint64_t n;
	static uint64_t mod, inv, r2;
	Mint() : n(0) { }
	Mint(const uint64_t &x) : n(init(x)) { }
	static uint64_t init(const uint64_t &w) { return reduce(__uint128_t(w) * r2); }
	static void set_mod(const uint64_t &m) {
		mod = inv = m;
		for (int i = 0; i < 5; i++) {
			inv *= 2 - inv * m;
		}
		r2 = -__uint128_t(m) % m;
	}
	static uint64_t reduce(const __uint128_t &x) {
		uint64_t y = uint64_t(x >> 64) - uint64_t((__uint128_t(uint64_t(x) * inv) * mod) >> 64);
		return int64_t(y) < 0 ? y + mod : y;
	}
	Mint& operator+= (const Mint &x) { n += x.n - mod; if (int64_t(n) < 0) n += mod; return *this; }
	Mint& operator+ (const Mint &x) const { return Mint(*this) += x; }
	Mint& operator*= (const Mint &x) { n = reduce(__uint128_t(n) * x.n); return *this; }
	Mint& operator* (const Mint &x) const { return Mint(*this) *= x; }
	uint64_t val() const { return reduce(n); }
};

uint64_t Mint::mod, Mint::inv, Mint::r2;

bool suspect(const uint64_t &a, const uint64_t &s, uint64_t d, const uint64_t &n) {
	if (Mint::mod != n)  Mint::set_mod(n);
	Mint x(1), xx(a), one(x), minusone(n - 1);
	while (d > 0) {
		if (d & 1)
			x *= xx;
		xx *= xx;
		d >>= 1;
	}
	if (x.n == one.n)
		return true;
	for (unsigned int r = 0; r < s; r++) {
		if (x.n == minusone.n)
			return true;
		x *= x;
	}
	return false;
}

bool is_prime(const uint64_t &n) {
	if (n <= 1 || (n > 2 && (~n & 1)))
		return false;
	uint64_t d = n - 1, s = 0;
	while (~d & 1)
		s++,
		d >>= 1;
	static const uint64_t a_big[] = {
		2,
		325,
		9375,
		28178,
		450775,
		9780504,
		1795265022
	};
	static const uint64_t a_smol[] = {
		2,
		7,
		61
	};
	if (n <= 4759123141LL) {
		for (auto && p : a_smol) {
			if (p >= n)
				break;
			if (!suspect(p, s, d, n))
				return false;
		}
	}
	else {
		for (auto && p : a_big) {
			if (p >= n)
				break;
			if (!suspect(p, s, d, n))
				return false;
		}
	}
	return true;
}

// 2 to n primes
template<typename T = int>
vector<T> get_prime(T n) {
	vector<T> prime{2};
	for (int i = 3; i <= n; i += 2) {
		if (is_prime(i))
			prime.emplace_back(i);
	}
	return prime;
}

template<typename T = int>
void multiplier_zeta(vector<T>& arr) {
	assert(arr[0] == 0);
	int n = int(arr.size()) - 1;
	auto primes = get_prime(n);
	for (auto&p : primes) {
		for (int x = n / p; x >= 1; x--)
			arr[x] += arr[p * x];
	}
}

template<typename T = int>
void multiplier_mobius(vector<T>& arr) {
	assert(arr[0] == 0);
	int n = int(arr.size()) - 1;
	auto primes = get_prime(n);
	for (auto&p : primes) {
		for (int x = 1; x <= n / p; x++)
			arr[x] -= arr[x * p];
	}
}