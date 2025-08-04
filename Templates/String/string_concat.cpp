template<typename T = string>
T concat_string(T s1, int k) {
	T s(0, ' '); while (k--) { s += s1; }
	return s;
}