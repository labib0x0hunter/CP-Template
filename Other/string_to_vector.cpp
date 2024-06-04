vector<int> string_to_vector(const string &S, char first_char) {
	vector<int> vec(int(S.size()));
	for (int i = 0; i < int(S.size()); i++) {
		vec[i] = (S[i] != '?' ? S[i] - first_char : -1);
	}
	return vec;
}