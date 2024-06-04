string to_lower(string& s) {
	transform(s.begin(), s.end(), s.begin(), [](char c) { return tolower(c); });
	return s;
}

string to_upper(string& s) {
	transform(s.begin(), s.end(), s.begin(), [](char c) { return toupper(c); });
	return s;
}