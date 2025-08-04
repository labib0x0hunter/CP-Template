template<class T, class FUNCTION>
T lower_bound(T lo, T hi, FUNCTION&& f) {

	// first false
	T ans = -1;

	while (lo <= hi) {
		T mid = lo + (hi - lo) / 2;
		if (f(mid)) lo = mid + 1;
		else ans = mid, hi = mid - 1;
	}
	return ans;
}