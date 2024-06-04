#define LSONE(x) ((x) & -(x))
#define ONBIT(x, k) ((x) | (1ll << k))
#define OFFBIT(x, k) ((x) & (~ (1ll << k)))
#define IFONBIT(x, k) ((x >> k) & 1)
#define FLIPBIT(x, k) ((x) ^ (1ll << k))
#define ONBIT_AFTER_K(k) ((1ll << k) - 1)

int pop_count(int x) { return __builtin_popcount(x); }
// int pop_count(uint x) { return __builtin_popcount(x); }
// int pop_count(intll x) { return __builtin_popcountll(x); }
// int pop_count(uintll x) { return __builtin_popcountll(x); }
// (0, 1, 2, 3, 4) -> (-1, 0, 1, 1, 2)
int leading_one(int x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
// int leading_one(uint x) { return (x == 0 ? -1 : 31 - __builtin_clz(x)); }
// int leading_one(intll x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
// int leading_one(uintll x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }
// (0, 1, 2, 3, 4) -> (-1, 0, 1, 0, 2)
int tailing_zero(int x) { return (x == 0 ? -1 : __builtin_ctz(x)); }
// int tailing_zero(uint x) { return (x == 0 ? -1 : __builtin_ctz(x)); }
// int tailing_zero(intll x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }
// int tailing_zero(uintll x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }

// CPP-20
template<typename T = int>
int bit_length(T n) { return __bit_width(n); }
// 4 -> 4 , 5 -> 4 , 7 -> 4
template<typename T = int>
T prev_power_2(T n) { return __bit_floor(n); }
// 4 -> 4, 5 -> 8, 7 -> 8
template<typename T = int>
T next_power_2(T n) { __bit_ceil(n); }
template<typename T = int>
bool power_of_2(T n) { __has_single_bit(n); }

template<bool c = false, int NN = 32>
void print_binary(intll n) {
	int sizee = (c ? floorl(log2(n)) : NN);
	for (int i = sizee; i >= 0; i--) {
		cout << (IFONBIT(n, i) ? 1 : 0);
	} cout << endl;
}