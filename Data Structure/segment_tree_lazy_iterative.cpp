// unsigned int bit_ceil(unsigned int n) {
//     unsigned int x = 1;
//     while (x < (unsigned int)(n)) x *= 2;
//     return x;
// }

// int countr_zero(unsigned int n) {
//     return __builtin_ctz(n);
// }

template <class S,
          auto op,
          auto e,
          class F,
          auto mapping,
          auto composition,
          auto id>
struct segment_tree_lazy {
	static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
	              "op must work as S(S, S)");
	static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
	              "e must work as S()");
	static_assert(
	    std::is_convertible_v<decltype(mapping), std::function<S(F, S)>>,
	    "mapping must work as F(F, S)");
	static_assert(
	    std::is_convertible_v<decltype(composition), std::function<F(F, F)>>,
	    "compostiion must work as F(F, F)");
	static_assert(std::is_convertible_v<decltype(id), std::function<F()>>,
	              "id must work as F()");

	int _n, size, log;
	std::vector<S> d;
	std::vector<F> lz;

	segment_tree_lazy() : segment_tree_lazy(0) {}
	explicit segment_tree_lazy(int n) : segment_tree_lazy(std::vector<int>(n, 0)) {}
	explicit segment_tree_lazy(const std::vector<int>& v) : _n(int(v.size())) {
		size = (int)bit_ceil((unsigned int)(_n));
		log = countr_zero((unsigned int)size);
		d = std::vector<S>(2 * size, e());
		lz = std::vector<F>(size, id());
		for (int i = 0; i < _n; i++) d[size + i] = S{v[i], 1};  // Set value
		for (int i = size - 1; i >= 1; i--) {
			set(i);
		}
	}

	void set(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
	void all_apply(int k, F f) {
		d[k] = mapping(f, d[k]);
		if (k < size) lz[k] = composition(f, lz[k]);
	}
	void push(int k) {
		all_apply(2 * k, lz[k]);
		all_apply(2 * k + 1, lz[k]);
		lz[k] = id();
	}

	void update_(int p, S x) {
		p--;
		assert(0 <= p && p < _n);
		p += size;
		for (int i = log; i >= 1; i--) push(p >> i);
		d[p] = x;
		for (int i = 1; i <= log; i++) set(p >> i);
	}

	S get_(int p) {
		p--;
		assert(0 <= p && p < _n);
		p += size;
		for (int i = log; i >= 1; i--) push(p >> i);
		return d[p];
	}

	S query_(int l, int r) {
		l--;
		assert(0 <= l && l <= r && r <= _n);
		if (l == r) return e();
		l += size; r += size;
		for (int i = log; i >= 1; i--) {
			if (((l >> i) << i) != l) push(l >> i);
			if (((r >> i) << i) != r) push((r - 1) >> i);
		}
		S sml = e(), smr = e();
		while (l < r) {
			if (l & 1) sml = op(sml, d[l++]);
			if (r & 1) smr = op(d[--r], smr);
			l >>= 1; r >>= 1;
		}
		return op(sml, smr);
	}

	S all_prod() { return d[1]; }

	void apply(int p, F f) {
		p--;
		assert(0 <= p && p < _n);
		p += size;
		for (int i = log; i >= 1; i--) push(p >> i);
		d[p] = mapping(f, d[p]);
		for (int i = 1; i <= log; i++) set(p >> i);
	}

	void update_range(int l, int r, F f) {
		l--;
		assert(0 <= l && l <= r && r <= _n);
		if (l == r) return;
		l += size; r += size;
		for (int i = log; i >= 1; i--) {
			if (((l >> i) << i) != l) push(l >> i);
			if (((r >> i) << i) != r) push((r - 1) >> i);
		}
		{
			int l2 = l, r2 = r;
			while (l < r) {
				if (l & 1) all_apply(l++, f);
				if (r & 1) all_apply(--r, f);
				l >>= 1;
				r >>= 1;
			}
			l = l2; r = r2;
		}
		for (int i = 1; i <= log; i++) {
			if (((l >> i) << i) != l) set(l >> i);
			if (((r >> i) << i) != r) set((r - 1) >> i);
		}
	}

	template <class G> int max_right(int l, G g) {
		assert(0 <= l && l <= _n);
		assert(g(e()));
		if (l == _n) return _n;
		l += size;
		for (int i = log; i >= 1; i--) push(l >> i);
		S sm = e();
		do {
			while (l % 2 == 0) l >>= 1;
			if (!g(op(sm, d[l]))) {
				while (l < size) {
					push(l);
					l = (2 * l);
					if (g(op(sm, d[l]))) {
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

	template <class G> int min_left(int r, G g) {
		assert(0 <= r && r <= _n);
		assert(g(e()));
		if (r == 0) return 0;
		r += size;
		for (int i = log; i >= 1; i--) push((r - 1) >> i);
		S sm = e();
		do {
			r--;
			while (r > 1 && (r % 2)) r >>= 1;
			if (!g(op(d[r], sm))) {
				while (r < size) {
					push(r);
					r = (2 * r + 1);
					if (g(op(d[r], sm))) {
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

	template <bool (*g)(S)> int max_right(int l) {
		return max_right(l, [](S x) { return g(x); });
	}

	template <bool (*g)(S)> int min_left(int r) {
		return min_left(r, [](S x) { return g(x); });
	}

	void update(int l, int r, int f) {
		update_range(l, r, F{f});         // Change Data Type (F)
	}

	void update(int p, int x) {
		update_(p, S{x});             // Change Data Type (S)
	}

	int query(int l, int r) {
		return query_(l, r).value;   // Change Data Type (S)
	}

	int get(int x) {
		return get_(x).value;        // Change Data Type (S)
	}

};

struct node { long long L; };
struct S { long long value; int size; };

// S op(S a, S b) { return S{a.value + b.value, a.size + b.size}; } // Operation
// S e() {return S{0, 0};} // Out of range
// S mapping(node a, S b) { return S{b.value + 1ll * a.L * b.size, b.size};} // set value tree[n]
// node composition(node a, node b) { return node{a.L + b.L}; } // set lazy
// node id() { return node{0}; }  // initial value of lazy

/** min, max **/
/** For index use S and set tree[n] = S{arr[i], i}; **/
// long long op(long long a, long long b) { return min(a, b); } // Operation
// long long e() {return numeric_limits<int>::max();} // Out of range
// long long mapping(node a, long long b) { return a.L + b;} // set value tree[n]
// node composition(node a, node b) { return node{a.L + b.L}; } // set lazy
// node id() { return node{0}; }  // initial value of lazy

/** range sum **/
/** set tree[n] = S{arr[i], 1} **/
// S op(S a, S b) { return S{a.value + b.value, a.size + b.size}; } // Operation
// S e() {return S{0, 0};} // Out of range
// S mapping(node a, S b) { return S{b.value + 1ll * a.L * b.size, b.size};} // set value tree[n]
// node composition(node a, node b) { return node{a.L + b.L}; } // set lazy
// node id() { return node{0}; }  // initial value of lazy

/** min, max , tree[n] = x **/
/** For index use S and set tree[n] = S{arr[i], i}; **/
// long long ID = numeric_limits<long long>::max();
// long long op(long long a, long long b) { return min(a, b); } // Operation
// long long e() {return numeric_limits<int>::max();} // Out of range
// long long mapping(node a, long long b) { return (a.L == ID ? b : a.L);} // set value tree[n]
// node composition(node a, node b) { return (a.L == ID ? b : a); } // set lazy
// node id() { return node{ID}; }  // initial value of lazy

/** range sum , arr[n] = x **/
/** set tree[n] = S{arr[i], 1} **/
long long ID = numeric_limits<long long>::max();
S op(S a, S b) { return S{a.value + b.value, a.size + b.size}; } // Operation
S e() {return S{0, 0};} // Out of range
S mapping(node a, S b) {
	if (a.L != ID) b.value = 1ll * a.L * b.size;
	return b;
} // set value tree[n]
node composition(node a, node b) { return (a.L == ID ? b : a); } // set lazy
node id() { return node{ID}; }  // initial value of lazy

using Segment_tree_lazy = segment_tree_lazy<S, op, e, node, mapping, composition, id>;

// segment_tree_lazy<S, op, e, node, mapping, composition, id> seg(arr);

// segment_tree_lazy<S, op, e, node, mapping, composition, id> seg(arr);