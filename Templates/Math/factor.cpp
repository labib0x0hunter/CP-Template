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

uint64_t rho_pollard(const uint64_t &n) {
	if (~n & 1)
		return 2u;
	static random_device rng;
	uniform_int_distribution<uint64_t> rr(1, n - 1);
	if (Mint::mod != n)
		Mint::set_mod(n);
	for (;;) {
		uint64_t c_ = rr(rng), g = 1, r = 1, m = 500;
		Mint y(rr(rng)), xx(0), c(c_), ys(0), q(1);
		while (g == 1) {
			xx.n = y.n;
			for (unsigned int i = 1; i <= r; i++)
				y *= y,
				     y += c;
			uint64_t k = 0; g = 1;
			while (k < r && g == 1) {
				for (unsigned int i = 1; i <= (m > (r - k) ? (r - k) : m); i++) {
					ys.n = y.n;
					y *= y; y += c;
					uint64_t xxx = xx.val(), yyy = y.val();
					q *= Mint(xxx > yyy ? xxx - yyy : yyy - xxx);
				}
				g = __gcd<uint64_t>(q.val(), n);
				k += m;
			}
			r *= 2;
		}
		if (g == n)
			g = 1;
		while (g == 1) {
			ys *= ys; ys += c;
			uint64_t xxx = xx.val(), yyy = ys.val();
			g = __gcd<uint64_t>(xxx > yyy ? xxx - yyy : yyy - xxx, n);
		}
		if (g != n && is_prime(g))
			return g;
	}
	assert(69 == 420);
}

// O(cuberoot(N))
template <typename T>
vector<T> factor(T n) {
	if (n < 2)
		return { };
	if (is_prime(n))
		return {n};
	T d = rho_pollard(static_cast<uint64_t>(n));
	vector<T> left = factor<T>(d);
	vector<T> right = factor<T>(n / d);
	left.insert(left.end(), right.begin(), right.end());
	return left;
}

template<typename T = int>
vector<pair<T, int>> factorize(T n) {
	auto primes_fact = factor<T>(n);
	sort(primes_fact.begin(), primes_fact.end());
	if (primes_fact.empty())
		return {};
	vector<pair<T, int>> fact;
	T p = primes_fact[0];
	int cnt = 1;
	for (int i = 1; i < (int)primes_fact.size(); i++) {
		if (primes_fact[i] == p) cnt++;
		else {
			fact.emplace_back(p, cnt);
			p = primes_fact[i], cnt = 1;
		}
	}
	fact.emplace_back(p, cnt);
	return fact;
}

template<typename T = int>
int nod(vector<pair<T, int>>& fact) {
	int ans = 1;
	for (auto i : fact) ans *= 1ll * (i.second + 1);
	return ans;
}

template<typename T = int>
int nod(T n) {
	auto fact = factorize<T>(n);
	return nod(fact);
}

template<typename T = int>
T sod(vector<pair<T, int>>& fact) {
	T ans = 1;
	for (auto i : fact) {
		T p = i.first;
		T total = 1;
		int m = i.second;
		while (m--) {
			total += p;
			p *= 1ll * i.first;
		}
		ans *= 1ll * total;
	}
	return ans;
}

template<typename T = int>
T sod(T n) {
	auto fact = factorize<T>(n);
	return sod(fact);
}

template<typename T = int>
T phi(vector<pair<T, int>>& fact, T n) {
	if (n == 1) return 1;
	T ans = n;
	for (auto i : fact) ans -= (ans / i.first);
	return ans;
}

template<typename T = int>
T phi(T n) {
	auto fact = factorize<T>(n);
	return phi(fact, n);
}

template<typename T = int>
void generate_divisor(int idx, T div, vector<pair<T, int>>&fact, vector<T>& divisor) {
	if (idx == int(fact.size())) {
		divisor.emplace_back(div);
		return;
	}
	for (int i = 0; i <= fact[idx].second; i++) {
		generate_divisor(idx + 1, div, fact, divisor);
		div = 1ll * div * fact[idx].first;
	}
}

template<typename T = int>
vector<T> get_divisor(vector<pair<T, int>>&fact) {
	vector<T> divisor;
	generate_divisor((T)0, (T)1, fact, divisor);
	sort(divisor.begin(), divisor.end());
	return divisor;
}

// O(sqrt(n))
template<typename T = int>
vector<T> get_divisor(T n) {
	auto fact = factorize<T>(n);
	return get_divisor(fact);
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