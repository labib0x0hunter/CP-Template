mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

template<typename T>
T rand(T a, T b) {
	return uniform_int_distribution<T>(a, b)(rng);
}

const int sizee = int(2e6) + 10;
vector<uint64_t> hash_table(sizee + 10);
void calculation() {
	for (int i = 0; i <= sizee; i++)
		hash_table[i] = rand<uint64_t>(0, numeric_limits<uint64_t>::max());
}

struct Zobrist_hash {

	int N;
	vector<uint64_t> hash;

	Zobrist_hash(vector<int>& arr) {
		N = arr.size();
		hash.resize(N + 1, 0);
		build(arr);
	}

	// nlog(n)
	void build(vector<int>& arr) {
		set<int> seen;
		uint64_t H = 0;
		for (size_t i = 0; i < N; i++) {
			if (seen.find(arr[i]) == seen.end()) {
				seen.insert(arr[i]);
				H ^= hash_table[arr[i]];
			}
			hash[i + 1] = H;
		}
	}

	uint64_t query(int r) {
		return hash[r];
	}
};

// hash a set, not multiset
// 1 to r, For prefix only
// query(r) = hash(set(1, 1, 2, 3, 3, 2)) = hash(1, 2, 3)

// IMPRTANT ****
// call calculation()