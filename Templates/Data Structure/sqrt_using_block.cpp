template<typename T = int>
struct BLOCK {
	int N, block_size;
	vector<T> block;
	vector<int> A;
	BLOCK(int n) : BLOCK(vector<int>(n, 0)) {}
	BLOCK(vector<int>& arr) : A(arr) {
		N = int(arr.size());
		block_size = sqrt(N) + 1;
		block.resize(block_size, 0); // init_value
		for (int i = 0; i < block_size; i++)
			build_block(i);
	}

	// 0-index
	int block_id(int i) { return (i / block_size); }

	// build BLOCK b
	void build_block(int b) {
		int l = b * block_size;
		for (int i = l; i < (l + block_size) && i < N; i++)
			block[b] += A[i]; // Change Operation
	}

	// 1-index
	void update(int pos, T x) {
		int B = block_id(pos - 1);
		block[B] -= A[pos - 1]; // change OP
		A[pos - 1] = x;
		block[B] += A[pos - 1]; // cahnge OP
	}

	// 1-index
	void update_block(int pos, T x) {
		int B = block_id(pos - 1);
		A[pos - 1] = x;
		build_block(B);
	}

	// 1-index
	T query(int l, int r) {
		assert(1 <= l and l <= r and r <= N);
		l--, r--;
		T ans = 0; // Init Value
		for (; (l <= r) && (l % block_size != 0);) {
			ans += A[l]; // Cahnge OP
			l++;
		}
		for (; (l <= r) && (l + block_size - 1 <= r);) {
			int B = block_id(l);
			ans += block[B];   // Change OP
			l += block_size;
		}
		for (; l <= r; ) {
			ans += A[l];  // Change OP
			l++;
		}
		return ans;
	}
};
