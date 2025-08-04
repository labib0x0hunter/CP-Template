// a & a + 1 & .. & b - 1 & b
template<typename T = int>
T range_AND(T a, T b) {
	int bitt = 0;
	while (a != b and a > 0) {
		bitt++;
		a = a >> 1ll;
		b = b >> 1ll;
	}
	return ((T)a << bitt);
}