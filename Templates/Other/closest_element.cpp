template<typename T = int>
T findClosestNumber(set<T>& st, T x) {
	auto lb = st.lower_bound(x);
	auto res = (lb != st.end()) ? *lb : *st.rbegin();
	if (lb != st.begin()) {
		auto prev_ = prev(lb);
		if (abs(*prev_ - x) <= abs(*lb - x)) {
			res = *prev_;
		}
	}
	return res;
}
