// TC : O(n * m) / 64
// |s| = int(1e6) will give TLE
const int N = int(1e5 + 10);
vector<bitset<N>> bit(26);
bitset<N> ans;

void calculation(string& s) {
	for (int i = 0; i < 26; i++)
		bit[i] = bitset<N>(0);
	for (int i = 0; i < int(s.size()); i++)
		bit[s[i] - 'a'][i] = 1;
}

// how many time t occurs in s
int get_match(string& t) {
	ans = bitset<N>(0);
	ans = bit[t.front() - 'a'];
	for (int i = 1; i < int(t.size()); i++)
		ans = ans & (bit[t[i] - 'a'] >> i);
	return ans.count();
}

// find position of match
// call get_match(t) first
// print as (|s| - p - 1)
vector<int> get_poistion() {
	vector<int> I;
	I.push_back(ans._Find_first());
	while (ans._Find_next(I.back()) != N)
		I.push_back(ans._Find_next(I.back()));
	return move(I);
}