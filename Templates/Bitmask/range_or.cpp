// L or L + 1 or .. or R - 1 or R
template<typename T = int>
T range_OR(T L, T R) {
	if (!R) return 0;
	T res = 0;
	int P1 = leading_one(L);
	int P2 = leading_one(R);
	while (P1 == P2) {
		auto temp = (1ll << P1);
		res += temp;
		L -= temp; R -= temp;
		P1 = leading_one(L);
		P2 = leading_one(R);
	}
	for (int i = max(P1, P2); i >= 0; i--)
		res += (1ll << i);
	return res;
};