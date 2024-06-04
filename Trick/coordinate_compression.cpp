// Coordinate Compression
// 1-based index
template<typename T = int>
struct coordinate_compression {
	vector<T> brr;
	bool sorted = false;

	coordinate_compression() {}
	coordinate_compression(vector<T>&arr) {
		brr = arr;
	}

	void insert(T a) {
		brr.emplace_back(a);
	}

	void sortt() {
		sort(brr.begin(), brr.end());
		brr.erase(unique(brr.begin(), brr.end()), brr.end());
		sorted = true;
	}

	vector<int> get_id(vector<T>& arr) {
		for (auto &i : arr) {
			i = get_id(i);
		}
		return arr;
	}

	int get_id(T a) {
		if (sorted == false) sortt();
		return distance(brr.begin(),
		                lower_bound(brr.begin(), brr.end(), a)) + 1;
	}
};