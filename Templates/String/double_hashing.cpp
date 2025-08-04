// int primes[] = {285897553, 745494041, 693888673, 950758511, 282174533, 847345579, 722520917, 354688703, 963459817, 139793893};
int mod1 = 127657753, mod2 = 987654319;
int expo(long long x, long long y, int mod) {
	int ans = 1; x %= mod;
	while (y) {
		if (y & 1) ans = 1ll * ans * x % mod;
		x = 1ll * x * x % mod; y = y >> 1;
	}
	return (ans + mod) % mod;
}

using HASH = pair<int, int>;
HASH add(HASH a, HASH b) {
	HASH res;
	res.first = ((long long) a.first + b.first) % mod1;
	res.second = ((long long) a.second + b.second) % mod2;
	return res;
}

HASH subs(HASH a, HASH b) {
	HASH res;
	res.first = (a.first - b.first) % mod1;
	res.second = (a.second - b.second) % mod2;
	res.first = (res.first + mod1) % mod1;
	res.second = (res.second + mod2) % mod2;
	return res;
}

HASH mult(HASH a, HASH b) {
	HASH res;
	res.first = (1ll * a.first * b.first) % mod1;
	res.second = (1ll * a.second * b.second) % mod2;
	return res;
}

const int sizee = 2e5 + 10;
HASH pw{137, 277};
HASH invp{0, 0};
vector<HASH> power(sizee), invpower(sizee);

void calculation() {
	power[0] = {1, 1};
	for (int i = 1; i < sizee; i++) {
		power[i] = mult(power[i - 1], pw);
	}
	invp.first = expo(pw.first, mod1 - 2, mod1);
	invp.second = expo(pw.second, mod2 - 2, mod2);
	invpower[0] = {1, 1};
	for (int i = 1; i < sizee; i++) {
		invpower[i] = mult(invpower[i - 1], invp);
	}
}

struct hashing {
	int N;
	vector<HASH> hash; // 1 - indexed
	hashing() {}
	hashing(string s) { build(s); }

	void build(string &s) {
		N = int(s.size());
		hash.push_back({0, 0});
		for (int i = 0; i < N; i++) {
			HASH P = add(hash[i], mult(power[i], {s[i], s[i]}));
			hash.push_back(P);
		}
	}

	// hash = (h[r] - h[l - 1]) / p[l - 1]
	HASH query(int l, int r) { // 1 - indexed
		if (l > r) return {0, 0};
		if (l < 1 || r > N) return {0, 0};
		assert(1 <= l && l <= r && r <= N);
		HASH ans = mult(subs(hash[r], hash[l - 1]), invpower[l - 1]);
		return ans;
	}

	HASH rev_query(int l, int r) { return query(N - r + 1, N - l + 1); }
};

// hash = hash * power[p];
void hash_power_mul(HASH &a, int p) {
	a = mult(power[p], {p, p});
}

// a + b = ab
// hash = hash1 + hash2
// sizee is the len of string a
HASH hash_concat(HASH a, HASH b, int sizee) {
	HASH scaled_b = mult(b, power[size_a]);
	return add(a, scaled_b);
}

// a + bd + c = ac
// hash = abdc, rep = bd
// i = 2, j = 3, rep_len = 2
// replace hash i to j with rep , rep_len = len(rep)
HASH hash_replace(hashing& hash, HASH rep, int i, int j, int rep_len) {
	assert(1 <= i && i <= j && j <= hash.N);
	HASH prev{0, 0}, next{0, 0};
	if (i != 1) prev = hash.query(1, i - 1);
	if (j != hash.N) next = hash.query(j + 1, hash.N);
	HASH new_hash = hash_concat(prev, rep, i - 1);
	new_hash = hash_concat(new_hash, next, i + rep_len - 1);
	return new_hash;
}

// auto h = hashing("s1").hash_interval(1, 2);
// hashing b("3525235");
// auto h1 = b.hash_interval(1, 2);

// auto h1 = hash_s.hash_interval(i, j);
// auto h2 = hash_s.hash_interval_rev(n - j + 1, n - i + 1);

// IMPORTANT NOTESSSSSSSSS
/*
 * Remember to call calculation() function
 *
 */
