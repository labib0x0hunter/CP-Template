// O(log^2(n))
// last position in subarray starting from idx where f(a[idx], a[idx + 1], .. ) = a[idx]
int last_position(int idx, int k) {
	int lo = idx, hi = N;
	int ans = -1;
	while (lo <= hi) {
		int mid = lo + (hi - lo) / 2;
		// O(logn)
		if (query(idx, mid) == k)
			ans = mid,
			lo = mid + 1;
		else
			hi = mid - 1;
	}
	return ans;
}

// O(log^2(n))
// first position in subarray starting from idx where f(.. , a[idx - 1], a[idx]) = a[idx]
int first_position(int idx, int k) {
	int lo = 1, hi = idx;
	int ans = -1;
	while (lo <= hi) {
		int mid = lo + (hi - lo) / 2;
		// O(logn)
		if (query(mid, idx) == k)
			ans = mid,
			hi = mid - 1;
		else
			lo = mid + 1;
	}
	return ans;
};