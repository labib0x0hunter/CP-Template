// A class that manages a sequence.
// The following operations can be done in O(log N) time:
//  - Remove the first / last element
//  - Remove the smallest / largest element
//  - Push an element to the head / tail
//  - Retrieve the smallest / largest element
//  - Retrieve the median
//
// (More precisely, it stores a set of pairs (i, v) and manages minimum / maximum i and minimum / maximum / median of v)
// https://atcoder.jp/contests/abc324/tasks/abc324_g
class sequence {
public:
	using value_type = std::pair<unsigned, unsigned>;
	std::set<value_type> original, small, large;
	// Balances the sizes of the two sets to support median retrieval
	void balance() {
		while (std::size(small) > std::size(large)) {
			large.emplace_hint(std::begin(large), *std::prev(std::end(small)));
			small.erase(std::prev(std::end(small)));
		}
		while (std::size(small) + 1 < std::size(large)) {
			small.emplace_hint(std::end(small), *std::begin(large));
			large.erase(std::begin(large));
		}
	}
	value_type pop_helper(unsigned i, unsigned v) {
		original.erase(std::make_pair(i, v));
		small.erase(std::make_pair(v, i));
		large.erase(std::make_pair(v, i));
		balance();
		return {i, v};
	}
public:
	void swap(sequence &rhs) {
		using std::swap;
		swap(original, rhs.original);
		swap(small, rhs.small);
		swap(large, rhs.large);
	}
	sequence() = default;
	auto min() const {
		return std::begin(std::empty(small) ? large : small)->first;
	}
	auto mid() const {
		return std::begin(large)->first;
	}
	auto max() const {
		return std::prev(std::end(large))->first;
	}
	void emplace(unsigned long i, unsigned long v) {
		original.emplace(i, v);
		(v < mid() ? small : large).emplace(v, i);
		balance();
	}
	void emplace(const value_type &value) {
		emplace(value.first, value.second);
	}
	auto empty() const noexcept {
		return std::empty(original);
	}
	auto size() const noexcept {
		return std::size(original);
	}
	auto pop_front() {
		const auto[i, v] {*begin(original)};
		return pop_helper(i, v);
	}
	auto pop_back() {
		const auto[i, v] {*std::prev(std::end(original))};
		return pop_helper(i, v);
	}
	auto pop_min() {
		const auto[v, i] {*std::begin(std::empty(small) ? large : small)};
		return pop_helper(i, v);
	}
	auto pop_max() {
		const auto[v, i] {*std::prev(std::end(large))};
		return pop_helper(i, v);
	}
};