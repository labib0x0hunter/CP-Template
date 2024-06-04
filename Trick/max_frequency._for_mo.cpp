int maxx_freq = 0;
vector<int> mp(N + 1, 0);
vector<int> cnt(N + N + 10, 0);

// change here
auto add = [&](int idx) {
	if (idx == -1) return;
	int freq = mp[arr[idx]];
	cnt[freq + n]--;
	mp[arr[idx]]++;

	freq++;

	cnt[freq + n]++;
	if (maxx_freq < freq)
		maxx_freq++;
};

// change here
auto remove = [&](int idx) {
	if (idx == -1) return;
	int freq = mp[arr[idx]];
	cnt[freq + n]--;
	mp[arr[idx]]--;

	freq--;

	cnt[freq + n]++;
	if (cnt[maxx_freq + n] == 0)
		maxx_freq--;
};