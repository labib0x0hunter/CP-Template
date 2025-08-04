template<typename T = vector<int>>
void REMOVE_EMPTY_ARRAY(vector<T>& arr) {
	arr.erase( remove_if(arr.begin(), arr.end(), [&](const T & v) {
		return v.empty();
	}), arr.end());
}