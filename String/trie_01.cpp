struct vertex {
	bool exist;
	vector<int> child;
	int freq;

	vertex() {
		exist = false;
		freq = 0;
		child.assign(26, -1);
	}
};

struct Trie {

	int root, next;
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

	void insert(string word) {
		int cur = root;
		for (char c : word) {
			int alphabet_num = tolower(c) - 'a'; // Convert to lowercase
			if (TRIE[cur].child[alphabet_num] == -1) {
				if (next >= int(TRIE.size())) {   // Out of range add new vertex
					ADD_VERTEX();
				}
				TRIE[cur].child[alphabet_num] = next++;
			}
			cur = TRIE[cur].child[alphabet_num];
			// TRIE[cur].freq++;
		}
		TRIE[cur].freq++;
		TRIE[cur].exist = true;
	}

	// Erase a string from trie
	void erase(string word) {
		int cur = root;
		for (auto c : word) {
			int alphabet_num = tolower(c) - 'a';
			if (TRIE[cur].child[alphabet_num] == -1)
				return;
			cur = TRIE[cur].child[alphabet_num];
		}
		TRIE[cur].freq--;
		if (TRIE[cur].freq == 0)
			TRIE[cur].exist = false;
	}

	// Searches if word present in trie
	// Freq for frequency count
	bool search(string word) {
		int cur = root;
		for (auto c : word) {
			int alphabet_num = tolower(c) - 'a';
			if (TRIE[cur].child[alphabet_num] == -1)
				return false;
			cur = TRIE[cur].child[alphabet_num];
		}
		return TRIE[cur].exist;
	}

	// Return LCP sizes
	// change int to long long
	int LCP(string prefix) {
		int cur = root;
		int lcp_cnt = 0;
		for (auto c : prefix) {
			int alphabet_num = tolower(c) - 'a';
			if (TRIE[cur].child[alphabet_num] == -1) {
				break;
			}
			cur = TRIE[cur].child[alphabet_num];
			lcp_cnt++;
			// lcp_cnt += TRIE[cur].freq++;
		}
		return lcp_cnt;
	}
};

Trie tr;
void dfs(int cur) {
	for (int i = 0; i < 26; i++) {
		if (tr.TRIE[cur].child[i] == -1)
			continue;
		dfs(tr.TRIE[cur].child[i]);
	}
};

// tr = Trie(0);
