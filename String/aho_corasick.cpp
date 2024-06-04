struct Aho_corasick {
	struct node {
		map<char, node*> child;
		node* fail;
		vector<int> patIx;
	};

	node* root;
	int N;
	void move_(node*& kmp, int c) {
		while (!kmp -> child[c])
			kmp = kmp -> fail;
		kmp = kmp -> child[c];
	}

	Aho_corasick(int n) : N(n) {
		root = new node();
	}

	void insert(const string s, int idx) {
		node* temp = root;
		for (auto c : s) {
			char C = c;
			if (temp -> child[C] == nullptr)
				temp -> child[C] = new node();
			temp = temp -> child[C];
		}
		temp -> patIx.push_back(idx);
	}

	void build() {
		node* temp = root;
		queue<node*> q;
		for (char c = 'a'; c <= 'z'; c++) {
			if (temp -> child[c]) {
				q.push(temp -> child[c]);
				temp -> child[c] -> fail = root;
			}
			else temp -> child[c] = root;
		}
		for (char c = 'A'; c <= 'Z'; c++) {
			if (temp -> child[c]) {
				q.push(temp -> child[c]);
				temp -> child[c] -> fail = root;
			}
			else temp -> child[c] = root;
		}

		node* cur;
		while (!q.empty()) {
			cur = q.front();
			q.pop();
			for (char c = 'a'; c <= 'z'; c++) {
				if (cur -> child[c] == nullptr) continue;
				q.push(cur -> child[c]);
				node* kmp = cur -> fail;
				move_(kmp, c);
				cur -> child[c] -> fail = kmp;
				cur -> child[c] -> patIx.insert(cur -> child[c] -> patIx.end(), kmp -> patIx.begin(), kmp -> patIx.end());
			}

			for (char c = 'A'; c <= 'Z'; c++) {
				if (cur -> child[c] == nullptr) continue;
				q.push(cur -> child[c]);
				node* kmp = cur -> fail;
				move_(kmp, c);
				cur -> child[c] -> fail = kmp;
				cur -> child[c] -> patIx.insert(cur -> child[c] -> patIx.end(), kmp -> patIx.begin(), kmp -> patIx.end());
			}
		}
	}

	vector<vector<int>> match_(const string s) {
		vector<vector<int>> res(N);
		node* temp = root;
		for (int i = 0; i < s.size(); i++) {
			char c = s[i];
			move_(temp, c);
			for (auto j : temp -> patIx)
				res[j].push_back(i);
		}
		return move(res);
	}
};