// unsigned int bit_ceil(unsigned int n) {
// 	unsigned int x = 1;
// 	while (x < (unsigned int)(n)) x *= 2;
// 	return x;
// }

// int countr_zero(unsigned int n) {
// 	return __builtin_ctz(n);
// }

template <class S, auto op, auto e>
struct segment_tree {
	static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
	              "op must work as S(S, S)");
	static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
	              "e must work as S()");

	int _n, size, log;
	vector<S> d;

	segment_tree() : segment_tree(0) {}
	explicit segment_tree(int n) : segment_tree(std::vector<int>(n, 0)) {}
	explicit segment_tree(const std::vector<int>& v) : _n(int(v.size())) {
		size = bit_ceil((unsigned int)(_n));
		log = countr_zero((unsigned int)size);
		d = std::vector<S>(2 * size, e());
		for (int i = 0; i < _n; i++) d[size + i] = v[i]; // Set value
		for (int i = size - 1; i >= 1; i--) {
			set(i);
		}
	}

	void set(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }

	// To increase by x: d[p] += x;
	void update_(int p, S x) {
		p--;
		assert(0 <= p && p < _n);
		p += size;
		d[p] = x;    // Replace in Array
		for (int i = 1; i <= log; i++) set(p >> i);
	}

	S query_(int l, int r) {
		l--;
		assert(0 <= l && l <= r && r <= _n);
		S sml = e(), smr = e();
		l += size; r += size;
		while (l < r) {
			if (l & 1) sml = op(sml, d[l++]);
			if (r & 1) smr = op(d[--r], smr);
			l >>= 1; r >>= 1;
		}
		return op(sml, smr);
	}

	S all_prod() { return d[1]; }
	S get_(int p) const { p--; assert(0 <= p && p < _n); return d[p + size]; }

	template <class F>
	int max_right(int l, F f) const {
		assert(0 <= l && l <= _n);
		assert(f(e()));
		if (l == _n) return _n;
		l += size;
		S sm = e();
		do {
			while (l % 2 == 0) l >>= 1;
			if (!f(op(sm, d[l]))) {
				while (l < size) {
					l = (2 * l);
					if (f(op(sm, d[l]))) {
						sm = op(sm, d[l]);
						l++;
					}
				}
				return l - size;
			}
			sm = op(sm, d[l]);
			l++;
		} while ((l & -l) != l);
		return _n;
	}

	template <class F>
	int min_left(int r, F f) const {
		assert(0 <= r && r <= _n);
		assert(f(e()));
		if (r == 0) return 0;
		r += size;
		S sm = e();
		do {
			r--;
			while (r > 1 && (r % 2)) r >>= 1;
			if (!f(op(d[r], sm))) {
				while (r < size) {
					r = (2 * r + 1);
					if (f(op(d[r], sm))) {
						sm = op(d[r], sm);
						r--;
					}
				}
				return r + 1 - size;
			}
			sm = op(d[r], sm);
		} while ((r & -r) != r);
		return 0;
	}

	// 0-index based
	template <bool (*f)(S)> int max_right(int l) const {
		return max_right(l, [](S x) { return f(x); });
	}

	// This one should be tested
	template <bool (*f)(S)> int min_left(int r) const {
		return min_left(r, [](S x) { return f(x); });
	}

	void update(int p, int x) {
		update_(p, S(x));          // Change Data Type(S)
	}

	int query(int l, int r) {
		return query_(l, r);       // Change Data Type(S)
	}

	int get(int p) {
		return get_(p);           // Change Data Type(S)
	}
};

struct node
{
	using T = int;
	T v;
	node(T V) { v = V; }
};

// Operation
int OP(int a, int b) { return min(a, b); }
// Out of Range
int E() { return numeric_limits<int>::max(); }

// int target;
// bool F(int v) { return v > target; }

using Segment_tree = segment_tree<int, op, e>;

// ** NOTE ** Works with cpp20
// 1-index based
// segment_tree<int, OP, E> seg(arr);
// seg.max_right<F>(index)

// TODO -> kth one

// max segment tree
// max_right<F>(i) : Finds the first j such that i <= j <= n and target <= ai
// IF not found then returns n + 1
// return v < target
