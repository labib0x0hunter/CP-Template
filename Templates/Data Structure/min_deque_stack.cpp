template<typename T = int>
struct minstack {
	stack<pair<T, T>> st;
	T getmin() {return st.top().second;}
	bool empty() {return st.empty();}
	int size() {return st.size();}
	void push(T x) {
		T mn = x;
		if (!empty()) mn = min(mn, getmin());
		st.push({x, mn});
	}
	void pop() {st.pop();}
	T top() {return st.top().first;}
	void swap(minstack &x) {st.swap(x.st);}
};

template<typename T = int>
struct mindeque {
	minstack<T> l, r, t;
	void rebalance() {
		bool f = false;
		if (r.empty()) {f = true; l.swap(r);}
		int sz = r.size() / 2;
		while (sz--) {t.push(r.top()); r.pop();}
		while (!r.empty()) {l.push(r.top()); r.pop();}
		while (!t.empty()) {r.push(t.top()); t.pop();}
		if (f) l.swap(r);
	}
	T getmin() {
		if (l.empty()) return r.getmin();
		if (r.empty()) return l.getmin();
		return min(l.getmin(), r.getmin());
	}
	bool empty() {return l.empty() && r.empty();}
	int size() {return l.size() + r.size();}
	void push_front(T x) {l.push(x);}
	void push_back(T x) {r.push(x);}
	void pop_front() {if (l.empty()) rebalance(); l.pop();}
	void pop_back() {if (r.empty()) rebalance(); r.pop();}
	T front() {if (l.empty()) rebalance(); return l.top();}
	T back() {if (r.empty()) rebalance(); return r.top();}
	void swap(mindeque &x) {l.swap(x.l); r.swap(x.r);}
};