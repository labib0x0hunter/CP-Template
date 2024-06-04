// merge y into x
template<typename T = set<int>>
void small_to_large(T& x, T& y) {
	if (x.size() < y.size())
		x.swap(y);
	for (auto i : y)
		x.insert(i);
	y.clear();
}