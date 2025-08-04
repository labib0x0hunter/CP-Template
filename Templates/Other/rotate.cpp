// 1-based
// Cyclic-rotation l to r by k times
template<typename T>
T rotate_k(T& arr, int l, int r, int k) {
	rotate(&arr[l - 1], &arr[r - k], &arr[r]);
	return arr;
}