#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct fast_hash_pair {
	static uint64_t splitmix64(uint64_t x) {
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	template <typename T, typename U>
	size_t operator()(const std::pair<T, U>& p) const {
		static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
		size_t hash_first = splitmix64(std::hash<T> {}(p.first) + FIXED_RANDOM);
		size_t hash_second = splitmix64(std::hash<U> {}(p.second) + FIXED_RANDOM);
		return hash_first ^ hash_second;
	}
};

gp_hash_table<pair<int, int>, bool, fast_hash_pair> found;
