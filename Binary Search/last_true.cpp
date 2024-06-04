template<class T, class FUNCTION>
T upper_bound(T lo, T hi, FUNCTION&& f) {

	// last true
	T ans = -1;

	while (lo <= hi) {
		T mid = lo + (hi - lo) / 2;
		if (f(mid)) ans = mid, lo = mid + 1;
		else hi = mid - 1;
	}
	return ans;
}