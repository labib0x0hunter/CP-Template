#define int128 __int128_t
istream& operator >> (istream& in, int128 &value) { string s; in >> s; value = 0; for (int i = (s.front() == '-' ? 1 : 0) ; i < s.size(); i++) { value = value * 10 + (s[i] - '0'); } if (s.front() == '-') { value *= -1; } return in; }
ostream& operator << (ostream& os, int128 &value) { string s; int128 temp = value; if (temp == 0) { s = "0";} if (temp < 0) {temp *= -1;} while (temp) { s += '0' + (temp % 10); temp /= 10; } if (value < 0) { s.push_back('-');} reverse(s.begin(), s.end()); os << s; return os; }
