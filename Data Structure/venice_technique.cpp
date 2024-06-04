template<typename T = int>
struct Venice {
	long long sum = 0;
	multiset<T> Q;
	void push(T x) {
		x -= sum;
		Q.insert(x);
	}
	T pop() {
		auto ans = *Q.begin();
		Q.erase(Q.begin());
		ans += sum;
		return ans;
	}
	int size() { return Q.size(); }
	void add(long long x) { sum += x; }
	void merge(Venice &&x) {
		if (size() < x.size()) swap(sum, x.sum), swap(Q, x.Q);
		for (auto i : x) {
			i -= sum;
			Q.insert(i);
		}
	}
};