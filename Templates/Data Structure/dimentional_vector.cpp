template<int D, typename T> struct D_VECTOR : public vector < D_VECTOR < D - 1, T >> {
	static_assert(D >= 1, "Vector dimension must be greater than zero!");
	template<typename... Args>D_VECTOR(int n = 0, Args... args) : vector < D_VECTOR < D - 1, T >> (n, D_VECTOR < D - 1, T > (args...)) {}
};
template<typename T> struct D_VECTOR<1, T> : public vector<T> {
	D_VECTOR(int n = 0, const T& val = T()) : vector<T>(n, val) {}
};