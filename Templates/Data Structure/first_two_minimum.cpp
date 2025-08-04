template <class T, class S>
inline bool chmin(T &a, const S &b) {
	return (a > b ? a = b, 1 : 0);
}

template <typename T = int, typename KEY = int>
struct first_second_minn_01 {
	T min1 = infll, min2 = infll;
	KEY key1 = -1, key2 = -1;
	bool insert(T x, KEY key) {
		if (x > min1 and x > min2) return 0;
		if (x < min1) {
			min1 = x, key1 = key;
			if (min2 < min1) {
				swap(key1, key2); swap(min1, min2);
				return 1;
			}
		}
		if (x < min2) {
			min2 = x; key2 = key;
			if (min2 < min1) {
				swap(key1, key2); swap(min1, min2);
				return 1;
			}
		}
	}
};

template <typename T = int, typename KEY = int>
struct first_second_minn {
	T min1 = numeric_limits<int>::max(), min2 = numeric_limits<int>::max();
	KEY key1 = -1, key2 = -1;
	bool add_element(T x, KEY key) {
		if (key1 == key) { return chmin(min1, x); }
		if (key2 == key) {
			bool upd = chmin(min2, x);
			if (min1 > min2) swap(min1, min2), swap(key1, key2);
			return upd;
		}
		if (min1 > x) {
			min2 = min1, key2 = key1, min1 = x, key1 = key;
			return 1;
		}
		else if (min2 > x) {
			min2 = x, key2 = key;
			return 1;
		}
		return 0;
	}
};

// Stores the first and second minn, and their associate key