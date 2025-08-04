struct Manacher {
	vector<int> p[2];
	int N;
	Manacher(string s) {
		N = s.size();
		p[0].resize(N + 1);
		p[1].resize(N);
		for (int z = 0; z < 2; z++) {
			for (int i = 0, l = 0, r = 0; i < N; i++) {
				int t = r - i + !z;
				if (i < r) p[z][i] = min(t, p[z][l + t]);
				int L = i - p[z][i], R = i + p[z][i] - !z;
				while (L >= 1 && R + 1 < N && s[L - 1] == s[R + 1])
					p[z][i]++, L--, R++;
				if (R > r) l = L, r = R;
			}
		}
	}
	// 0-index
	bool is_palindrome(int l, int r) {
		int mid = (l + r + 1) / 2, len = r - l + 1;
		return 2 * p[len % 2][mid] + len % 2 >= len;
	}

	// Max palindrome length, 0-index
	int max_size(int i) {
		int odd_len = 2 * p[1][i] + 1;
		int even_len = (i + 1 >= N ? 0 : 2 * p[0][i + 1]);
		return max(odd_len, even_len);
	}

	// 0-index
	pair<int, int> get_range(int i, bool odd = true) {
		if (odd) return {i - p[1][i], i + p[1][i]};
		else {
			if (i + 1 >= N) return { -1, -1};
			if (p[0][i + 1] == 0) return { -1, -1};
			return {max(0, i - p[0][i + 1] + 1), min(N - 1, i + p[0][i + 1])};
		}
	}

	// total palindrome
	intll count() {
		intll ans = 0;
		for (auto i : p[0]) ans += 1ll * i;
		for (auto i : p[1]) ans += 1ll * i;
		return ans;
	}
};

// p[1][i] = (max odd length palindrome centered at i) / 2 [floor division]
// p[0][i] = (max even length palindrome centered at i) / 2 [floor divison] (Right center)
// e.g. for s = "abbabba", p[1][3] = 3, p[0][2] = 2
// abba -> p[0][2] = 2 (0-based index)