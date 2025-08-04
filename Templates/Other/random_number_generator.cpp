// mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template<typename T>
T rand(T a, T b) {
	return uniform_int_distribution<T>(a, b)(rng);
}