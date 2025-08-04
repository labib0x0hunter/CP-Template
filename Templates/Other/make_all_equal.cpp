// Given a list of values, finds the minimum total amount of movement needed to make them all equal.
template<typename T1, typename T2> T1 min_equal_distance(vector<T2> &values) {
	if (values.empty())
		return 0;

	int n = int(values.size());
	nth_element(values.begin(), values.begin() + n / 2, values.end());
	T2 median = values[n / 2];
	T1 total = 0;

	for (T2 x : values)
		total += abs(x - median);

	return total;
}

// Given a list of values, finds the minimum total amount of movement to make them contiguous (x, x + 1, x + 2, ...).
template<typename T1, typename T2> T1 min_contiguous_distance(vector<T2> values) {
	if (!is_sorted(values.begin(), values.end()))
		sort(values.begin(), values.end());

	for (int i = 0; i < int(values.size()); i++)
		values[i] -= i;

	return min_equal_distance<T1>(values);
}

/**
 * cout << min_equal_distance<int>(index) << endl;
 * cout << min_contiguous_distance<int>(index) << endl;
 **/