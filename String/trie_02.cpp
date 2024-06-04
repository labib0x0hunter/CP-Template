struct vertex {
	vector<int> child;
	int freq;

	vertex() {
		freq = 0;
		child.assign(2, -1);
	}
};

struct Trie {

	int root, next;
	int N = 31;
	vector<vertex> TRIE;

	Trie() : Trie(0) {}
	Trie(int n) {
		TRIE.resize(n + 1);
		root = 0;
		next = 1;
	}

	void ADD_VERTEX() {
		TRIE.push_back(vertex());
	}

	void insert(int word) {
		int cur = root;
		for (int i = N; i >= 0; i--) {
			int alphabet_num = (word >> i) & 1;
			if (TRIE[cur].child[alphabet_num] == -1) {
				if (next >= int(TRIE.size())) {   // Out of range add new vertex
					ADD_VERTEX();
				}
				TRIE[cur].child[alphabet_num] = next++;
			}
			cur = TRIE[cur].child[alphabet_num];
			TRIE[cur].freq++;
		}
	}

	// Erase a string from trie
	void erase(int word) {
		int cur = root;
		int prev = -1;
		for (int i = N; i >= 0; i--) {
			int alphabet_num = (word >> i) & 1;
			if (TRIE[cur].child[alphabet_num] == -1)
				return;
			prev = cur;
			cur = TRIE[cur].child[alphabet_num];
			TRIE[cur].freq--;
			if (TRIE[cur].freq == 0)
				TRIE[prev].child[alphabet_num] = -1;
		}
	}

	int max_XOR(int x) {
		int cur = root;
		int _ans = 0;
		for (int i = N; i >= 0; i--) {
			int alphabet_num = (x >> i) & 1;
			if (cur == -1) {
				_ans |= (alphabet_num == 1 ? (1 << i) : 0);
				continue;
			}
			if (TRIE[cur].child[1 ^ alphabet_num] == -1)
				cur = TRIE[cur].child[alphabet_num];
			else {
				_ans |= (1 << i);
				cur = TRIE[cur].child[1 ^ alphabet_num];
			}
		}
		return _ans;
	}

	int min_XOR(int x) {
		int cur = root;
		int _ans = 0;
		for (int i = N; i >= 0; i--) {
			int alphabet_num = (x >> i) & 1;
			if (TRIE[cur].child[alphabet_num] == -1) {
				if (alphabet_num ^ 1)
					_ans |= (1 << i);
				cur = TRIE[cur].child[1 ^ alphabet_num];
			}
			else {
				if (alphabet_num)
					_ans |= (1 << i);
				cur = TRIE[cur].child[alphabet_num];
			}
		}
		return _ans;
	}

	// number of values s.t. val ^ x < k
	long long LessThan(int x, int k) {
		int cur = root;
		long long ans = 0;
		for (int i = N; i >= 0; i--) {
			if (cur == -1) break;
			int b1 = (x >> i) & 1, b2 = (k >> i) & 1;
			if (b2 == 1) {
				if (TRIE[cur].child[b1] != -1) ans += 1ll * TRIE[TRIE[cur].child[b1]].freq;
				cur = TRIE[cur].child[b1 ^ 1];
			}
			else cur = TRIE[cur].child[b1];
		}
		return ans;
	}

	// *** unique elements are to be inserted
	// duplicate value will give WA
	// ans = mex(0)
	int mex(int x) {
		int cur = root;
		int m = 0;
		for (int i = N; i >= 0; i--) {
			int b = (x >> i) & 1;
			if (TRIE[cur].child[b] == -1) return m;
			if (TRIE[TRIE[cur].child[b]].freq == (1 << i)) {
				b ^= 1;
				m ^= (1 << i);
			}
			if (TRIE[cur].child[b] == -1) return m;
			cur = TRIE[cur].child[b];
		}
		assert(false);
	}
};

// prefix xor -> insert 0 to avoid WA