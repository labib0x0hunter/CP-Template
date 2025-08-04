// Counts the number of pairs i < j such that compare(values[i], values[j]) is true.
// greater<int>()
template<typename T, typename FF>
intll count_pairs(vector<T> values, FF &&compare) {
	vector<T> buffer(values.size());

	auto count = [&](auto && self, int start, int end) {
		if (end - start <= 1)
			return 0ll;

		int mid = (start + end) / 2;
		intll answer = self(self, start, mid) + self(self, mid, end);
		int left = start, right = mid, n = 0;

		while (left < mid || right < end)
			if (left < mid && (right == end || compare(values[left], values[right]))) {
				buffer[n++] = values[left++];
			} else {
				answer += left - start;
				buffer[n++] = values[right++];
			}

		copy(buffer.begin(), buffer.begin() + n, values.begin() + start);
		return answer;
	};

	return count(count , 0, int(values.size()));
}